#define PY_SSIZE_T_CLEAN
#include <Python.h>

/* must_be_positive(n) -> n, raises ValueError if n <= 0 */
static PyObject *
py_must_be_positive(PyObject *self, PyObject *args)
{
    long n;
    if (!PyArg_ParseTuple(args, "l", &n)) return NULL;
    // TODO: raise ValueError if n <= 0
    
    return PyLong_FromLong(n);
}

/* safe_divide(a, b) -> a/b, raises ZeroDivisionError if b == 0.0 */
static PyObject *
py_safe_divide(PyObject *self, PyObject *args)
{
    double a, b;
    if (!PyArg_ParseTuple(args, "dd", &a, &b)) return NULL;
    // TODO: raise ZeroDivisionError if b == 0.0
    return PyFloat_FromDouble(a / b);
}

/* string_length(obj) -> int, raises TypeError if obj is not a str */
static PyObject *
py_string_length(PyObject *self, PyObject *args)
{
    PyObject *obj;
    if (!PyArg_ParseTuple(args, "O", &obj)) return NULL;
    // TODO: check type with PyUnicode_Check, raise TypeError if not str
    //       use PyUnicode_GetLength to get the length
}

static PyMethodDef methods[] = {
    {"must_be_positive", py_must_be_positive, METH_VARARGS, "Return n or raise ValueError."},
    {"safe_divide",      py_safe_divide,      METH_VARARGS, "Return a/b or raise ZeroDivisionError."},
    {"string_length",    py_string_length,    METH_VARARGS, "Return len(s) or raise TypeError."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    .m_name    = "py_exceptions",
    .m_doc     = "Raising built-in exceptions exercise",
    .m_size    = -1,
    .m_methods = methods,
};

PyMODINIT_FUNC
PyInit_py_exceptions(void)
{
    return PyModule_Create(&moduledef);
}
