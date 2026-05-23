# CPython C Extension Exercises


Learning CPython internals by implementing Python modules and types in C using the Python/C API.

Disclaimer: The most of repo scaffolds were created by Claude. There is no pretense of this repo being precise, accurate and full course on the topic.

## How each exercise works

Each folder contains:
- `module.c` — the C extension to implement (you write this)
- `test_module.py` — tests that verify correctness (AI-generated, run to check your work)
- `Makefile` — builds the `.so` and runs tests

Build and test any exercise:
```bash
cd 01_basic_types/01_hello_module
make test
```

## Build reference

The core compile command (Makefiles wrap this):
```bash
gcc -shared -fPIC $(python3.13-config --includes --ldflags) -o mymodule.so mymodule.c
```

---

## Curriculum

### Chapter 1 — Basic Types

The foundation: how to define a module, expose functions, and exchange values between C and Python.

| Exercise | What you learn | Key API |
|---|---|---|
| `01_hello_module` | Module definition, a function that returns a string | `PyModuleDef`, `PyMethodDef`, `PyMODINIT_FUNC`, `PyUnicode_FromString` |
| `02_integers` | Accept and return Python ints from C | `PyArg_ParseTuple` with `"i"/"l"`, `PyLong_FromLong` |
| `03_floats_strings` | Accept floats and strings, return them | `"f"/"d"/"s"` format codes, `PyFloat_FromDouble`, `PyUnicode_*` |
| `04_multiple_args` | Multiple positional args, keyword args | `PyArg_ParseTupleAndKeywords`, `$` optional flag |

### Chapter 2 — Exceptions

How CPython signals errors: the error indicator, exception objects, and propagation through the call stack.

| Exercise | What you learn | Key API |
|---|---|---|
| `01_raise_builtin` | Raise `ValueError`, `TypeError`, `RuntimeError` from C | `PyErr_SetString`, `PyErr_Format`, `PyExc_*` |
| `02_custom_exception` | Define your own exception class in a C module | `PyErr_NewException`, storing on the module object |
| `03_exception_chaining` | Set `__cause__` and `__context__` from C | `PyException_SetCause`, `PyException_SetContext` |

### Chapter 3 — Sequences

Working with Python's built-in container types from C, then building your own type that supports the sequence protocol.

| Exercise | What you learn | Key API |
|---|---|---|
| `01_lists` | Create, read, modify Python lists in C | `PyList_New`, `PyList_Append`, `PyList_GetItem`, `PyList_SetItem` |
| `02_tuples` | Build and unpack tuples | `PyTuple_New`, `PyTuple_GetItem`, `PyTuple_Pack` |
| `03_dicts` | Create and query dicts | `PyDict_New`, `PyDict_SetItem`, `PyDict_GetItem`, `PyDict_Keys` |
| `04_custom_sequence` | A custom C type implementing `__len__` and `__getitem__` | `PyTypeObject`, `PySequenceMethods`, `sq_length`, `sq_item` |

### Chapter 4 — Memory Model

CPython uses reference counting. This chapter makes it concrete: when to incref, when to decref, what borrowed vs. stolen references mean, and how to catch leaks.

| Exercise | What you learn | Key API / tools |
|---|---|---|
| `01_refcounting` | Observe refcounts change; manually inc/dec | `Py_INCREF`, `Py_DECREF`, `sys.getrefcount` |
| `02_ownership` | Borrowed vs. stolen references; double-free vs. leak | `Py_XINCREF`, `Py_XDECREF`, `Py_CLEAR` |
| `03_valgrind` | Detect real memory leaks with Valgrind | `valgrind --leak-check=full`, Python's `Py_Finalize` |

### Chapter 5 — Iterators

Implement stateful iteration in C: the iterator protocol (`__iter__` / `__next__`), then attach an iterator to the custom sequence type from Chapter 3.

| Exercise | What you learn | Key API |
|---|---|---|
| `01_simple_iterator` | A standalone iterator object that counts from 0 to N | `tp_iter`, `tp_iternext`, `PyExc_StopIteration` |
| `02_stateful_iterator` | An iterator that filters or transforms on the fly | Internal C state in `PyObject` struct |
| `03_custom_type_iter` | Add iteration to the custom sequence from Chapter 3 | Wire `tp_iter` on `PyTypeObject` to return a separate iterator type |

### Chapter 7 — The GIL and Performance

The GIL prevents true parallelism in pure Python threads. A C extension can
release it during CPU-bound work, letting other threads run. This chapter
makes the difference measurable.

The same task (summing a large integer array) is implemented three ways,
benchmarked with `threading` and `time`:

| Exercise | What you learn | Key API |
|---|---|---|
| `01_benchmark` | Establish baseline: pure Python vs C with GIL held | `timeit`, `threading.Thread` |
| `02_release_gil` | Release the GIL in C, measure the speedup | `Py_BEGIN_ALLOW_THREADS`, `Py_END_ALLOW_THREADS` |

### Chapter 8 — Callbacks

Calling Python functions from C — the reverse of everything in Chapters 1–5.
Used for sort keys, event handlers, filter functions passed into C code.

| Exercise | What you learn | Key API |
|---|---|---|
| `01_simple_callback` | Accept a Python callable, call it with arguments, return the result | `PyObject_Call`, `PyCallable_Check` |
| `02_callback_exceptions` | Detect and propagate exceptions raised inside a callback | `PyErr_Occurred`, returning NULL from callback context |

### Chapter 9 — Buffer Protocol

Zero-copy data sharing between Python objects. When `memoryview`, NumPy,
and Pillow pass raw memory between each other without copying — that's the
buffer protocol. A C extension can both consume buffers from Python objects
and expose its own internal memory as a buffer.

| Exercise | What you learn | Key API |
|---|---|---|
| `01_read_buffer` | Accept any buffer-compatible object (`bytes`, `bytearray`, `memoryview`, NumPy array) and read its raw bytes without copying | `PyArg_ParseTuple` with `"y*"`, `Py_buffer`, `PyBUF_SIMPLE`, `PyBuffer_Release` |
| `02_expose_buffer` | Make a custom C type expose its internal array as a `memoryview` | `PyBufferProcs`, `bf_getbuffer`, `bf_releasebuffer` |

### Chapter 6 — Extensions in Other Languages

The C API is the foundation — every other approach compiles down to it or wraps it.
Each exercise re-implements the same small module (basic types, a custom type, error handling)
so you can compare the ergonomics directly against the C version.

| Exercise | Language | Toolchain | What you learn |
|---|---|---|---|
| `01_rust_pyo3` | Rust | PyO3 + maturin | Safe, ergonomic extension development; how PyO3 maps to raw C API calls |
| `02_cpp_pybind11` | C++ | pybind11 + CMake | Wrapping existing C++ code; how pybind11 handles type conversion |
| `03_cython` | Cython | Cython + setuptools | Python-like syntax compiled to C; bridging Python and C types |
| `04_cffi` | C via CFFI | cffi | Calling existing compiled libraries without writing extension boilerplate |

---

## Concepts map

```
Python/C API
├── Value exchange      ← Chapter 1
├── Error signaling     ← Chapter 2
├── Container types     ← Chapter 3 (01–03)
├── Custom types        ← Chapter 3 (04) + Chapter 5
├── Reference counting  ← Chapter 4
├── Iteration protocol  ← Chapter 5
├── Other languages     ← Chapter 6
├── GIL / performance   ← Chapter 7
├── Callbacks           ← Chapter 8
└── Buffer protocol     ← Chapter 9
```

## Useful references

- [Python/C API Reference](https://docs.python.org/3/c-api/index.html)
- [Extending Python with C](https://docs.python.org/3/extending/extending.html)
- [Defining Extension Types](https://docs.python.org/3/extending/newtypes_tutorial.html)
- [PyO3 Guide](https://pyo3.rs)
- [pybind11 Docs](https://pybind11.readthedocs.io)
- [Cython Docs](https://cython.readthedocs.io)