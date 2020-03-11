#include <vector>
#include <tuple>

typedef std::vector<float> FloatArray;
typedef std::tuple<FloatArray, FloatArray> ResultTuple;

typedef struct {
	int controlNum = 28;
	int maxIterNum = 30;
	double alpha = 0.002;
	double beta = 0.005;
	double epsilon = 0.001;
    // The resolution of the curve when discretized
	double internal = 0.002;
} settings;

ResultTuple py_fit(FloatArray input, settings& nCol);
void py_interface(char * input);
