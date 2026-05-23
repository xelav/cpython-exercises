#define PY_SSIZE_T_CLEAN
#include <Python.h>

/*
 * parse_int(s) -> int
 * Converts a str to int. On failure, raises ValueError chained from the
 * original exception — equivalent to: raise ValueError("...") from original
 */
static PyObject *
py_parse_int(PyObject *self, PyObject *args)
{
    const char *s;
    if (!PyArg_ParseTuple(args, "s", &s)) return NULL;

    // TODO:
    // 1. Call PyLong_FromString(s, NULL, 10) to attempt conversion
    // 2. If it fails, fetch the current exception with PyErr_GetRaisedException
    //    (this clears the error indicator)
    // 3. Build a new ValueError with PyErr_Format
    // 4. Fetch that new exception, set original as __cause__ with PyException_SetCause
    // 5. Set the new exception as current with PyErr_SetRaisedException
    // 6. Return NULL
    Py_RETURN_NONE;
}

/*
 * load_value(d, key) -> int
 * Looks up key in dict d and returns it as int.
 * Raises KeyError (missing) or TypeError (wrong type), both chained.
 */
static PyObject *
py_load_value(PyObject *self, PyObject *args)
{
    PyObject *d, *key;
    if (!PyArg_ParseTuple(args, "OO", &d, &key)) return NULL;

    // TODO:
    // 1. PyDict_GetItemWithError(d, key) — returns NULL+KeyError if missing
    // 2. Check type with PyLong_Check, chain TypeError if wrong
    // 3. Return PyLong_AsLong result
    Py_RETURN_NONE;
}

static PyMethodDef methods[] = {
    {"parse_int",   py_parse_int,   METH_VARARGS, "str -> int, chaining on failure."},
    {"load_value",  py_load_value,  METH_VARARGS, "dict, key -> int, chaining on failure."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    .m_name    = "py_exc_chain",
    .m_doc     = "Exception chaining exercise",
    .m_size    = -1,
    .m_methods = methods,
};

PyMODINIT_FUNC
PyInit_py_exc_chain(void)
{
    return PyModule_Create(&moduledef);
}
