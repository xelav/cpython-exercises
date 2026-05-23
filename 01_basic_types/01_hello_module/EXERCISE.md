# 01 — Hello Module

Implement a C extension module named `py_hello` that exposes a single function:

```python
py_hello.hello() -> str
```

It should return the string `"Hello from C!"`.

## Goals

- Understand the minimum structure a C extension needs to be importable by Python
- Know what `PyModuleDef`, `PyMethodDef`, and `PyMODINIT_FUNC` are for
- Successfully compile a `.so` and import it

## Build

```bash
gcc -shared -fPIC $(python3.13-config --includes --ldflags) -o py_hello.so py_hello.c
```

Then in the same directory:

```bash
python3 -c "import py_hello; print(py_hello.hello())"
```
