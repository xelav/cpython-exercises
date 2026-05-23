#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <math.h>

/* Return the area of a circle given its radius (float) */
static PyObject *
py_circle_area(PyObject *self, PyObject *args)
{
    // TODO: parse one double, return pi * r * r as a Python float
    // Hint: "d" format code, PyFloat_FromDouble, M_PI from <math.h>
    double r;
    PyArg_ParseTuple(args, "d", &r);
    double result = M_PI * r * r;
    return PyFloat_FromDouble(result);

}

/* Return the string s repeated n times */
static PyObject *
py_repeat(PyObject *self, PyObject *args)
{
    // TODO: parse a str and an int, return the repeated string
    // Hint: "si" format codes, PyUnicode_FromString or PySequence_Repeat
    int n;
    char* str;
    PyArg_ParseTuple(args, "si", &str, &n);
    char * result = malloc(n * strlen(str) + 1);
    result[0] = '\0';
    while (n--) {
        strcat(result, str);
    }
    return PyUnicode_FromString(result);
}

static PyMethodDef methods[] = {
    {"circle_area", py_circle_area, METH_VARARGS, "Return pi * r^2."},
    {"repeat",      py_repeat,      METH_VARARGS, "Return s repeated n times."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    .m_name    = "py_types",
    .m_doc     = "Float and string operations exercise",
    .m_size    = -1,
    .m_methods = methods,
};

PyMODINIT_FUNC
PyInit_py_types(void)
{
    return PyModule_Create(&moduledef);
}
