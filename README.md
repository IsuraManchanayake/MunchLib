# MunchLib

My own library for Python, with some useful functions and classes written in C++. It's most definitely not useful for
you. But I hope it may helps someone who needs to write functions in C++ and use them in Python.

## Building the library for Python

### Requirements
```bash
pip install -r requirements.txt
pip install -r requirements-tests.txt  # Optional
```

### Building the wheel
```bash
python setup.py sdist bdist_wheel
```

Find the wheel in the `dist` directory.

### Installing the wheel in any python environment
```bash
pip install dist/wheel_name.whl
```

Alternatively, install the wheel inplace and use it in the current environment.

```bash
python setup.py build_ext --inplace    
```

## Run tests

```bash
python test.py
```

## Using the library

```python
from munchlib.fruchterman import calculate_fruchterman_reingold_layout


G = nx.Graph()
G.add_edge(1, 2)
G.add_edge(2, 3)

result = calculate_fruchterman_reingold_layout(G, speed=1, area=10000, gravity=10, iter=100)
print(result)
check = (result == [(5856.415361084446, 8340.49794343261), (8490.599268826549, 8384.600107049415), (6129.310269828168, 3778.0931618983454)])
if check:
    print(f'Test passed')
else:
    print(f'Test failed')
```
