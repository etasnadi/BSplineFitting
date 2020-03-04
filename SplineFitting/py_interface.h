#include <vector>
#include <tuple>

typedef std::vector<float> FloatArray;
typedef std::tuple<FloatArray, FloatArray> ResultTuple;

ResultTuple py_fit(FloatArray input, int nCol);
void py_interface(char * input);
