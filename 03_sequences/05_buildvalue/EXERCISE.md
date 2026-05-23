# 05 — Py_BuildValue

## Goal

`Py_BuildValue` is the counterpart to `PyArg_ParseTuple` — instead of unpacking
Python objects into C variables, it builds Python objects from C values using a
format string.

## What to implement

A module with functions that return compound values, using `Py_BuildValue`
instead of manually constructing objects:

| Function | Returns | Format |
|---|---|---|
| `minmax(a, b, c)` | `(min, max)` tuple of ints | `"(ii)"` |
| `stats(values)` | `{"min": x, "max": y, "sum": z}` dict | `"{sisisisi}"` ... explore the dict format |
| `pair(a, b)` | `[a, b]` as a Python list | `"[ii]"` |

## Why here (Chapter 3)

`Py_BuildValue` shines when returning structured types — tuples, lists, dicts.
Those are the focus of this chapter, so it fits naturally alongside the other
sequence exercises.

## Before starting

Read the full format string table in the docs:
https://docs.python.org/3/c-api/arg.html#c.Py_BuildValue

Pay attention to: `"()"` for tuples, `"[]"` for lists, `"{}"` for dicts,
and how nested formats work.

## Status: stub — generate exercises when reaching this chapter
