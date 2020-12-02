import inspect
from functools import partial, wraps
from collections import UserDict
from typing import Callable, Tuple, Mapping, Any


class LazyProperty(object):
    """Lazy property for caching computed properties"""

    def __init__(self, func):
        self.func = func

    def __get__(self, instance, owner):
        if instance is None:
            return self
        else:
            value = self.func(instance)
            setattr(instance, self.func.__name__, value)
            return value


class NodupsDict(UserDict):
    def __setitem__(self, key, value):
        if key in self:
            raise RuntimeError(
                f"Can't register method with the same name: '{key}' multiple times.")
        super().__setitem__(key, value)


class multi_methods(object):
    # TODO Add support for descriptor.G
    # How to compitable with ray?
    """Dispatch multi methods through attributes fetching"""

    def __new__(cls, func=None, **kwargs):
        if func is None:
            return partial(cls, **kwargs)
        else:
            return super().__new__(cls)

    def __init__(self, func=None, **kwargs):
        self._func = func
        self._global_config = kwargs
        self._methods = NodupsDict()

    def __get__(self, instance, owner):
        @wraps(self._func)
        def sub_method(obj, *args, **kwargs):
            if args or kwargs:
                for _name in fn_names:
                    sub_method.__dict__[_name] = partial(
                        sub_method.__dict__[_name],
                        *args,
                        **kwargs
                    )
            return sub_method

        fn_names = self._methods.keys()
        bound_method = type(self.register)
        for name in fn_names:
            method = self._methods[name]
            if instance is not None:
                sub_method.__dict__[name] = bound_method(method, instance)
            else:
                sub_method.__dict__[name] = method

        self.__doc__ = self._doc
        sub_method.__doc__ = self._doc
        if instance is not None:
            return bound_method(sub_method, instance)
        else:
            return sub_method

    def __set__(self):
        raise PermissionError("Not allowed.")

    @LazyProperty
    def _doc(self):
        num = len(self._methods)
        methods = '\n' + '\n'.join(f"{name}:\n{fn.__doc__}"
                                   for name, fn in self._methods.items())
        doc_template = self.__dict__.get('__doc__', None)
        if doc_template is None:
            doc_template = "{methods}"

        return doc_template.format(num=num, methods=methods)

    def __call__(self, func=None, **kwargs):
        if func is None:
            return partial(self, **kwargs)
        else:
            return self.register(func, **kwargs)

    def register(self, func=None, **kwargs):
        if func is None:
            return partial(self.register, **kwargs)
        else:
            func.__name__ = func.__name__.strip('_')
            self._methods[func.__name__] = func


class AttrWrapper(object):

    def __init__(self,
                 input_handler: Callable[[Callable, Tuple,
                                          dict, dict], Tuple[Tuple, dict]] = None,
                 output_handler: Callable[[Callable, Tuple, dict, dict, Any], Any] = None):
        self.input_handler = input_handler
        self.output_handler = output_handler

    def __call__(self, attr, attr_obj):
        if inspect.isroutine(attr_obj):
            fn = attr_obj
            origin_params = inspect.signature(fn).parameters

            @wraps(fn)
            def wrapper(*args, **kwargs):
                # handle input args
                kwargs, extra_kwargs = self._extract_extra_kargs(
                    origin_params, kwargs)
                if self.input_handler:
                    args, kwargs = self.input_handler(
                        fn, args, kwargs, extra_kwargs)
                    kwargs, extra_kwargs = self._extract_extra_kargs(
                        origin_params, kwargs)
                # call original function
                result = fn(*args, **kwargs)
                # handle outputs of original function
                if self.output_handler:
                    result = self.output_handler(
                        fn, args, kwargs, extra_kwargs, result)

                return result

            return wrapper
        else:
            if self.output_handler is not None:
                attr_obj = self.output_handler(None, attr_obj)
            return attr_obj

    @staticmethod
    def _extract_extra_kargs(params: Mapping[str, inspect.Parameter], kwargs: dict):
        extra_kwargs, remain_kwargs = {}, {}
        for k, v in kwargs:
            if k in params:
                remain_kwargs[k] = v
            else:
                extra_kwargs[k] = v
        return remain_kwargs, extra_kwargs

    @classmethod
    def wrap_attr(cls, wrap_cls, predicate: Callable[[str, object], bool], wrapper: 'AttrWrapper'):
        import inspect
        for attr, _ in inspect.getmembers(wrap_cls):
            # raw object without obj.xx
            attr_obj = inspect.getattr_static(wrap_cls, attr)
            if predicate(attr, attr_obj):
                setattr(wrap_cls, attr, wrapper(attr, attr_obj))
