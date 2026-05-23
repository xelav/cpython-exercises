#define PY_SSIZE_T_CLEAN
#include <Python.h>

/*
 * greet(name, greeting="Hello") -> "{greeting}, {name}!"
 * Demonstrates optional keyword arguments from C.
 */
static PyObject *
py_greet(PyObject *self, PyObject *args, PyObject *kwargs)
{
    // TODO: parse positional + optional keyword args
    // Hint: PyArg_ParseTupleAndKeywords, kwlist, "|s" for optional,
    //       PyUnicode_FromFormat for string formatting

    int ok;
    char* name;
    static char* keywords[]  = {"", "greeting", NULL};
    char* greeting = "Hello";
    ok = PyArg_ParseTupleAndKeywords(args, kwargs, "s|s", keywords, &name, &greeting);
    if (!ok) return NULL;

    // This was a cool way to shoot myself in the leg
    // Weirdly this passes pytest!
    // result for some reason will have a valid pointer to heap 
    //   and sprintf will work fine
    // printf("%s, %s!", greeting, name);
    // char* result;
    // sprintf(result, "%s, %s!", greeting, name);
    // return PyUnicode_FromString(result);

    return PyUnicode_FromFormat("%s, %s!", greeting, name);
}

/*
 * sum_all(*args) -> int
 * Accepts any number of integer arguments, returns their sum.
 * Here args is already a Python tuple — iterate it directly.
 * Hint: PyTuple_Size, PyTuple_GetItem, PyLong_AsLong
 */
static PyObject *
py_sum_all(PyObject *self, PyObject *args)
{
    // TODO: iterate over args tuple, accumulate sum, return it

    Py_ssize_t args_num;
    args_num = PyTuple_Size(args);
    if (args_num < 0) return NULL;

    long sum = 0;
    for (Py_ssize_t i=0; i < args_num; i++){
        PyObject* obj;
        obj = PyTuple_GetItem(args, i);

        if (!PyLong_Check(obj)) {
            PyErr_Format(PyExc_TypeError, "expected int, got %s", Py_TYPE(obj)->tp_name);
            return NULL;
        }
        long j = PyLong_AsLong(obj);
        sum += j;
    }

    return PyLong_FromLong(sum);
    
}

static PyMethodDef methods[] = {
    // Note: METH_VARARGS | METH_KEYWORDS because py_greet accepts kwargs
    {"greet", (PyCFunction)py_greet, METH_VARARGS | METH_KEYWORDS,
     "greet(name, greeting='Hello') -> str"},
    {"sum_all", py_sum_all, METH_VARARGS, "sum_all(*args) -> int"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    .m_name    = "py_args",
    .m_doc     = "Multiple and keyword arguments exercise",
    .m_size    = -1,
    .m_methods = methods,
};

PyMODINIT_FUNC
PyInit_py_args(void)
{
    return PyModule_Create(&moduledef);
}
