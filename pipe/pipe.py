from inspect import isgenerator, isfunction

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn import datasets


class Pipe(object):
    def __init__(self, fn):
        self.fn = fn
        self.stream = []

    @property
    def x(self):
        return self.stream[-1]

    @x.setter
    def x(self, value):
        self.stream.append(value)

    def __or__(self, other):
        if isgenerator(other):
            self.x = other
        elif callable(other):
            self.x = other(self.x)
        else:
            self.x = other

        return self

    def __call__(self, inputs=None, res=True):
        if inputs is not None:
            self.x = inputs
        self.fn(p=self)
        if res:
            return self.x
        else:
            return self


p = Pipe(
    lambda p: p
    | p.x[np.cos(p.x) >= 10]
    | (i ** 2 for i in p.x)
    | list
    | plt.plot(p.x) | print('done')
)
p(np.arange(20))

Pipe(
    lambda p: p | np.linspace(
        0, 2*np.pi, 100) | np.sin | plt.plot
)()

iris = datasets.load_iris()
iris = pd.DataFrame(iris.data, columns=iris.feature_names)
print(iris.shape)
iris.head()

Pipe(
    lambda p: p | iris | p.x[p.x['sepal width (cm)'] > 3.2] | p.x.shape[0]
)()
