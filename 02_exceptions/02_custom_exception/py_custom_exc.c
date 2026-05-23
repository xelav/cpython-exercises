#define PY_SSIZE_T_CLEAN
#include <Python.h>

/* Module-level exception object — set during PyInit */
static PyObject *ModuleError = NULL;

/* validate_range(n, lo, hi) -> n, raises ModuleError if out of range */
static PyObject *
py_validate_range(PyObject *self, PyObject *args)
{
    long n, lo, hi;
    if (!PyArg_ParseTuple(args, "lll", &n, &lo, &hi)) return NULL;
    // TODO: raise ModuleError if n < lo or n > hi
    return PyLong_FromLong(n);
}

/* parse_version("major.minor.patch") -> (major, minor, patch) tuple
 * Raises ModuleError on bad format */
static PyObject *
py_parse_version(PyObject *self, PyObject *args)
{
    const char *s;
    if (!PyArg_ParseTuple(args, "s", &s)) return NULL;
    // TODO: split s on '.', validate 3 parts, convert each to int
    //       raise ModuleError on bad format
    //       return a tuple with PyTuple_Pack or Py_BuildValue
    Py_RETURN_NONE;
}

static PyMethodDef methods[] = {
    {"validate_range", py_validate_range, METH_VARARGS, "Return n or raise ModuleError."},
    {"parse_version",  py_parse_version,  METH_VARARGS, "Parse 'x.y.z' or raise ModuleError."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    .m_name    = "py_custom_exc",
    .m_doc     = "Custom exception type exercise",
    .m_size    = -1,
    .m_methods = methods,
};

PyMODINIT_FUNC
PyInit_py_custom_exc(void)
{
    PyObject *m = PyModule_Create(&moduledef);
    if (m == NULL) return NULL;

    // TODO: create ModuleError with PyErr_NewException("py_custom_exc.ModuleError", NULL, NULL)
    // TODO: add to module with PyModule_AddObjectRef(m, "ModuleError", ModuleError)
    // TODO: return NULL and clean up if either step fails

    return m;
}
