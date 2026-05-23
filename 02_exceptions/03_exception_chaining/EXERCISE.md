# 03 — Exception Chaining

## Goal

Implement the C equivalent of `raise Y from X` — setting `__cause__` on a
new exception so the original context is preserved and visible in tracebacks.

## Functions to implement

```python
parse_int(s: str) -> int
```
Converts a string to int. If conversion fails, catches the error and raises
a `ValueError` with a descriptive message, chaining the original exception
as `__cause__`.

In Python this would be:
```python
try:
    return int(s)
except ValueError as e:
    raise ValueError(f"cannot parse {s!r} as int") from e
```

```python
load_value(d: dict, key: str) -> int
```
Looks up `key` in `d` and returns it as int. Raises `KeyError` if missing,
`TypeError` if the value is not an int — both chained from the original error.

## Key API

- `PyErr_Fetch` / `PyErr_Restore` — save and restore the current exception
- `PyException_SetCause(new_exc, old_exc)` — sets `__cause__`, implies `__suppress_context__ = True`
- `PyException_SetContext(new_exc, old_exc)` — sets `__context__` (implicit chaining)
- `PyErr_SetRaisedException` (Python 3.12+) — cleaner alternative

## Note

This exercise requires understanding that the error indicator is a global
thread-local slot. Fetching it clears it — you must restore or discard it
explicitly.
