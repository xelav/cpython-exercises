#define PY_SSIZE_T_CLEAN
#include <Python.h>

/* Return the sum of two Python ints */
static PyObject *
py_add(PyObject *self, PyObject *args)
{
    // TODO: parse two ints from args, return their sum
    // Hint: PyArg_ParseTuple, "ii" format, PyLong_FromLong
    long a, b;
    PyArg_ParseTuple(args, "ll", &a, &b);
    long result = a + b;
    return PyLong_FromLong(result);
}

/* Return the absolute value of a Python int */
static PyObject *
py_absolute(PyObject *self, PyObject *args)
{
    // TODO: parse one int, return its absolute value
    long a;
    PyArg_ParseTuple(args, "l", &a);
    return PyLong_FromLong(abs(a));
}

static PyMethodDef methods[] = {
    {"add",      py_add,      METH_VARARGS, "Return a + b."},
    {"absolute", py_absolute, METH_VARARGS, "Return |n|."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    .m_name    = "py_integers",
    .m_doc     = "Integer operations exercise",
    .m_size    = -1,
    .m_methods = methods,
};

PyMODINIT_FUNC
PyInit_py_integers(void)
{
    return PyModule_Create(&moduledef);
}
