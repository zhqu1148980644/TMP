import io
from threading import Thread
from functools import partial
from subprocess import Popen, PIPE
from inspect import isgenerator, isfunction
from typing import Callable
from pathlib import Path

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn import datasets

__all__ = ['P', 'p', 'END']

def auto_open(filename, *args, **kwargs):
    return open(filename, *args, **kwargs)


def wfile_fn(file, *args):
    def write_file(input_stream):
        try:
            fhd = auto_open(file, *args)
        except:
            fhd = file
        fhd.writelines(input_stream)
        fhd.close()
        return fhd

    return write_file


class PipeBase(object):
    # TODO support Pipe(filename)  mode.
    def __init__(self, fns):
        try:
            fns[0]
        except TypeError:
            fns = [fns]
        self.fns = fns
        self.stream = []
        self.running = False

    @property
    def x(self):
        return self.stream[-1] if self.stream else None

    @x.setter
    def x(self, value):
        self.stream.append(value)

    def __or__(self, rop):
        self.handle_sibling(rop)
        if isgenerator(rop) or not isgenerator(rop) and not callable(rop):
            self.x = rop
        else:
            self.x = rop(self.x)
        return self

    def handle_sibling(self, rop):
        if isinstance(rop, self.__class__):
            raise NotImplementedError("Not implemented.!")

    def __add__(self, pipe):
        return self.__class__(self.fns + pipe.fns)

    def __call__(self, inputs=None, res=False):
        self.running = True
        self.stream = []
        if inputs is not None:
            self.x = inputs
        for fn in self.fns:
            fn(p=self)
        self.running = False
        if res:
            return self.x
        else:
            return self


class FileMixin(object):
    # 'test.file' | p
    def __ror__(self, lop):
        try:
            lop = auto_open(lop)
        except:
            pass

        try:
            self.x
            available = True
        except IndexError:
            available = False

        if not self.running:
            return self(lop)

        if not available:
            self.x = lop
        return self

    # 'test.file' >> p
    def __rrshift__(self, lop):
        return lop | self

    # p   >>  'test.file'
    def __rshift__(self, rop):
        self.handle_sibling(rop)
        return self + Pipe(lambda p: p | wfile_fn(rop, 'a+'))

    # p   >   'test.file'
    def __gt__(self, rop):
        self.handle_sibling(rop)
        return self + Pipe(lambda p: p | wfile_fn(rop, 'w'))


class Pipe(PipeBase, FileMixin):
    def __init__(self, fns):
        super().__init__(fns)
        self._threads = []

    def __or__(self, rop):
        if isinstance(rop, str):
            self.x = self.subp_stdout(rop)
        else:
            super().__or__(rop)

        return self

    # TODO store subp or stdout ?
    def subp_stdout(self, rop):
        def write_to_stdin(instream, outfd):
            for line in instream:
                outfd.write(bytes(line, encoding="utf-8"))
            outfd.close()
        p = Popen(rop, stdin=PIPE, stdout=PIPE, shell=True)
        if self.x is not None:
            t = Thread(target=write_to_stdin, args=(self.x, p.stdin))
            t.start()
            self._threads.append(t)

        return io.TextIOWrapper(p.stdout, encoding="utf-8")

    def __call__(self, *args, **kwargs):
        res = super().__call__(*args, **kwargs)
        for t in self._threads:
            t.join()
        return res


class Singleton(type):
    def __init__(self, *args, **kwargs):
        self.__instance = None
        super().__init__(*args, **kwargs)

    def __call__(self, *args, **kwargs):
        if self.__instance is None:
            self.__instance = super().__call__(*args, **kwargs)
        return self.__instance


class EasyPipe(Pipe, metaclass=Singleton):
    END = "END"

    def __init__(self):
        super().__init__(lambda x: x)

    def __call__(self, *args, **kwargs):
        raise NotImplementedError

    def __or__(self, rop):
        if rop != self.END:
            return super().__or__(rop)

        self._threads = []
        self.stream = []
        self.fns = []
        return self.x

    def __ror__(self, lop):
        self._threads = []
        self.stream = []
        try:
            if Path(lop).exists():
                lop = auto_open(lop)
            else:
                raise FileNotFoundError(lop)
        except:
            pass

        self.x = lop

        return self

    # p   >>  'test.file'
    def __rshift__(self, rop):
        self.handle_sibling(rop)
        self | wfile_fn(rop, 'a+')
        return self

    # p   >   'test.file'
    def __gt__(self, rop):
        self.handle_sibling(rop)
        self | wfile_fn(rop, 'w')
        return self

P = Pipe
p = EasyPipe()
END = EasyPipe.END