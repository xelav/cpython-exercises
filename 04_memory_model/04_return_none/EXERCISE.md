# 04 — Py_RETURN_NONE and returning singletons

## Status: discuss before implementing

This exercise requires understanding reference counting first (exercises 01–03).
Come back here after completing those.

## Topic

Returning `None`, `True`, `False` from C is not as simple as `return Py_None`.
These are singletons — shared objects with a refcount that must be managed.

Covers: `Py_RETURN_NONE`, `Py_RETURN_TRUE`, `Py_RETURN_FALSE`,
and why the naive `return Py_None` is a latent bug.
