#define PY_SSIZE_T_CLEAN
#include <Python.h>

PyObject* print_hello(PyObject* self, PyObject* args)
{
    char* output = "Hello World!";
    printf(output);
    return PyUnicode_FromString(output);
}

static PyMethodDef module_methods[] = {
    {
        .ml_name = "hello",
        .ml_meth = print_hello,
        .ml_flags = METH_VARARGS,
        .ml_doc = "Print hello msg"
    },
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "py_hello",
    .m_doc = "Hello world exercise module",
    .m_methods = module_methods
};

PyMODINIT_FUNC
PyInit_py_hello(void)
{
    return PyModuleDef_Init(&module);
}