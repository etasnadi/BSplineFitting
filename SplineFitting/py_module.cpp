#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "py_interface.h"

static PyObject *SplError;

static std::vector<float> to_vec(PyObject *self, PyObject *args)
{
    PyObject *float_list;
    int pr_length;
    double *pr;

    std::vector<float> empty;
    std::vector<float> result;

    if (!PyArg_ParseTuple(args, "O", &float_list))
        return empty;
    pr_length = PyObject_Length(float_list);
    if (pr_length < 0)
        return empty;
    pr = (double *) malloc(sizeof(double *) * pr_length);
    if (pr == NULL)
        return empty;
    for (int index = 0; index < pr_length; index++) {
        PyObject *item;
        item = PyList_GetItem(float_list, index);
        if (!PyFloat_Check(item))
            pr[index] = 0.0;
        
        result.push_back(float(PyFloat_AsDouble(item)));
    }
    return result;
}

static PyObject* to_pyObject(std::vector<float>& data){
    srand(time(NULL));
    int N = data.size();
    PyObject* python_val = PyList_New(N);
    for (int i = 0; i < N; ++i)
    {
        PyObject* python_int = Py_BuildValue("f", data[i]);
        PyList_SetItem(python_val, i, python_int);
    }
    return python_val;
}

static PyObject *
pysplfit_fit(PyObject *self, PyObject *args){
    int nCol = 3;
    auto input = to_vec(self, args);
    auto result = py_fit(input, nCol);
    
    auto controls = std::get<0>(result);
    auto contour = std::get<1>(result);
    
    auto controls_py = to_pyObject(controls);
    auto contour_py = to_pyObject(contour);
    
    return Py_BuildValue("(O,O)", controls_py, contour_py);
}

static PyMethodDef SplMethods[] = {
    {"fit",  pysplfit_fit, METH_VARARGS,
     "Fit the B-Spline to the points."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef splmodule = {
    PyModuleDef_HEAD_INIT,
    "pysplfit",   /* name of module */
    NULL, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    SplMethods
};

PyMODINIT_FUNC
PyInit_pysplfit(void)
{
    PyObject *m;

    m = PyModule_Create(&splmodule);
    if (m == NULL)
        return NULL;

    SplError = PyErr_NewException("spl.error", NULL, NULL);
    Py_XINCREF(SplError);
    if (PyModule_AddObject(m, "error", SplError) < 0) {
        Py_XDECREF(SplError);
        Py_CLEAR(SplError);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}
