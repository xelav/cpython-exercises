# Handover

## Setup

- Dev container: GCC, GDB, Valgrind, python3.13-dev, uv
- Venv: `/workspaces/cpython_exercies/.venv` — pytest installed
- VS Code IntelliSense configured: `.vscode/c_cpp_properties.json` points to `/usr/include/python3.13`
- All modules use **single-phase initialization**: `m_size = -1` + `PyModule_Create`

Build command (what all Makefiles wrap):
```bash
gcc -shared -fPIC $(python3.13-config --includes --ldflags) -o <module>.so <module>.c
```

Run tests from any exercise directory:
```bash
make test
```

---

## Chapter 1 — Basic Types

### `01_hello_module` — DONE
- `py_hello.c` implemented, compiles and passes tests
- No Makefile (was the first exercise, built manually)
- Known quirk: uses `printf` + returns the string — `printf` uses a variable as format string, which is a `-Wformat-security` warning. Not a bug for this exercise.
- Module init uses `PyModuleDef_Init` (multi-phase, `m_size` defaults to 0) — differs from later exercises which use `PyModule_Create`. Both work, just inconsistent.

### `02_integers` — DONE
- `py_integers.c` implemented: `add(a, b)` and `absolute(n)`
- Uses `PyArg_ParseTuple` with `"ll"` format, `PyLong_FromLong`
- Has Makefile, passes tests

### `03_floats_strings` — IN PROGRESS
- `py_circle_area` — implemented, looks correct
- `py_repeat` — implemented, but `result` buffer from `malloc` is never `free`d — memory leak
  - Fix: call `free(result)` after `PyUnicode_FromString(result)` but before returning
- Has Makefile, not yet verified passing

### `04_multiple_args` — DONE
- `py_greet(name, greeting="Hello")` — implemented with `PyArg_ParseTupleAndKeywords`, `PyUnicode_FromFormat`
- `py_sum_all(*args)` — implemented by iterating args tuple with `PyTuple_Size` / `PyTuple_GetItem` / `PyLong_AsLong`
- Has positive + negative tests (TypeError cases). Subprocess test pattern added for clean-stack validation.
- Makefile uses `-Wall -Wuninitialized -Werror`

#### Deep dive: uninitialized pointer false positive
Investigated a case where `result = char*` (uninitialized) caused tests to pass under pytest but segfault in `run.py`. Root cause confirmed via GDB + ASan + `/proc/self/maps`:
- pytest's deep call stack left a valid heap pointer (`0x2da7cb08`, inside `[heap]` region) in `result`'s stack slot
- `run.py`'s shallow call stack left an unmapped partial address (`0x738b00000000`)
- Fix: `-Wall -Werror` at compile time + `= NULL` initialization + subprocess tests

---

## Chapters 2–5 — Not started

Directories created. Stubs added:
- `03_sequences/05_buildvalue/` — `Py_BuildValue` exercises (tuples, lists, dicts as return values)
- `04_memory_model/04_return_none/` — `Py_RETURN_NONE` / singleton returns — discuss before implementing

See `README.md` for full curriculum.

---

## Known issues in Chapter 1 (not fixed — awareness for next time)

| File | Issue |
|---|---|
| `py_integers.c`, `py_types.c` | `PyArg_ParseTuple` return value never checked → silent failure on wrong types |
| `py_types.c` `py_repeat` | `malloc`'d buffer never `free`d → memory leak |
| `py_args.c` `py_sum_all` | `PyLong_AsLong` result not checked → silent overflow |
| `py_hello.c` | `printf(output)` → format string bug; `print_hello` not `static` |
| `py_integers.c` | `abs()` used on `long` → should be `labs()` |
| all | TODO comments and dead code left in |

**The pattern:** almost every CPython API function can fail. Always check return values and propagate NULL.

---

## Key things learned / gotchas

| Topic | Note |
|---|---|
| `PyModuleDef_Init` vs `PyModule_Create` | `PyModuleDef_Init` is multi-phase (needs `m_size >= 0`). `PyModule_Create` is single-phase (`m_size = -1`). Use `PyModule_Create` for all exercises. |
| `-o` flag | Source file goes at the end without `-o`. Two `-o` flags corrupts the source file. |
| `static` on functions | Keeps C symbols local to the `.so`, good practice. |
| `METH_VARARGS \| METH_KEYWORDS` | Required when the function accepts `PyObject *kwargs`. Cast to `(PyCFunction)`. |
| `printf(variable)` | Format string bug — use `printf("%s", str)` instead. |
| `strcat` | Does not allocate. Destination must be writable + large enough. Always `malloc(len * n + 1)` and set `result[0] = '\0'` before using. |
| `malloc` in C extensions | You own the memory. Free it before returning (after converting to a Python object). |