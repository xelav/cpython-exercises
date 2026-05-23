# 01 — Raising Built-in Exceptions

## Goal

Raise Python's built-in exceptions from C: `ValueError`, `TypeError`,
`ZeroDivisionError`. Understand `PyErr_SetString`, `PyErr_Format`,
and the contract of always returning NULL after setting an error.

## Functions to implement

```python
must_be_positive(n: int) -> int
```
Returns `n` unchanged. Raises `ValueError` if `n <= 0`.

```python
safe_divide(a: float, b: float) -> float
```
Returns `a / b`. Raises `ZeroDivisionError` if `b == 0.0`.

```python
string_length(obj) -> int
```
Returns `len(obj)`. Raises `TypeError` if `obj` is not a str.
Use `PyUnicode_Check` to detect the type and `Py_TYPE(obj)->tp_name`
in the error message.

## Key API

- `PyErr_SetString(PyExc_ValueError, "message")`
- `PyErr_Format(PyExc_TypeError, "expected str, got %s", Py_TYPE(obj)->tp_name)`
- Every path that raises an exception must `return NULL`
- Every path that succeeds must NOT have an exception set
