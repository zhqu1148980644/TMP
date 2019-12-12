### A toy pipe.


#### Example

##### Basic

```python

from pipe import P

pipe = P(
    lambda p: p
    | p.x[np.cos(p.x) >= 10]
    | (i ** 2 for i in p.x)
    | list
    | plt.plot(p.x) | print('done')
)
pipe(np.arange(20))

P(
    lambda p: p
    | np.linspace(0, 2*np.pi, 100) | np.sin | plt.plot
)()

iris = datasets.load_iris()
iris = pd.DataFrame(iris.data, columns=iris.feature_names)
print(iris.shape)
iris.head()

P(
    lambda p: p
    | iris
    | p.x[p.x['sepal width (cm)'] > 3.2]
    | p.x.shape[0]
)()

pipe = P(
    lambda p: "testfile" >> p
    | (line for line in p.x)
) > "another_file"

pipe = P(
    lambda p: "testfile" >> p
    | (line for line in p.x)
    | (line + "haha" for line in p.x)
) >> "another_file1"

pipe()
"another_file" | pipe
"another_file" >> pipe
['asda', "asdas", "qweqw"] >> pipe


pipe = P(
    lambda p: p
    | (str(i) + "\n" for i in p.x)
    | "grep 1"
    | (int(i) for i in p.x)
    | list
    | print(p.x)
)

(i for i in range(20)) >> pipe
```

##### Easy Mode

```python
from pipe import p, END

[1, 2, 3, 4, 5] | p | (f"{x}\n" for x in p.x) > "another_file1"
(p | [2, 3, 4, 5] | (f"{x * 10 + 2}\n" for x in p.x)) >> "another_file1"
"another_file1" >> p | (x.rstrip() for x in p.x) | list | END

p | 10 | range | list | print(p.x) | END

[1, 2, 3, 4] >> p | (i ** 2 for i in p.x) | list | END
```

##### With callable function

```python
from pipe import p, END

def dedup(key=lambda x: x):
    def gen(iterable):
        seen = set()
        for item in iterable:
            dupkey = key(item)
            if dupkey not in seen:
                seen.add(dupkey)
                yield item
    return gen

p | [1, 2, -2 , 3, 3, -1, 3, 5] | dedup(key=lambda x: x < 0) | dedup() | list | END
```