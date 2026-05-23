# 02 — Custom Exception Types

## Goal

Define your own exception class in a C module and expose it as a module
attribute, so Python code can catch it by name: `except py_custom_exc.ModuleError`.

## What to implement

Define a `ModuleError` exception (subclass of `Exception`) on the module.
Then expose two functions:

```python
validate_range(n: int, lo: int, hi: int) -> int
```
Returns `n` if `lo <= n <= hi`. Raises `ModuleError` otherwise.

```python
parse_version(s: str) -> tuple[int, int, int]
```
Parses a `"major.minor.patch"` string. Raises `ModuleError` if the format
is wrong (wrong number of parts, non-integer components).

## Key difference from Chapter 1

`PyInit_*` can no longer just `return PyModule_Create(...)`. It must:
1. Create the module
2. Create the exception with `PyErr_NewException`
3. Add it to the module with `PyModule_AddObjectRef`
4. Return the module

## Key API

- `PyErr_NewException("py_custom_exc.ModuleError", NULL, NULL)`
- `PyModule_AddObjectRef(m, "ModuleError", ModuleError)`
- `PyErr_SetString(ModuleError, "message")`
