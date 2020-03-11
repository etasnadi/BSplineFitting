BSplineFitting (with Python interface)
==============

![Fitting a curve to 5 points.](/SplineFitting/demo.png)

Fitting cubic spline curve to 2d points

## Introduction ##

This is an implementation of paper "Fitting B-spline Curves to Point Clouds
by Curvature-Based Squared Distance Minimization".

Link to the paper: https://www.microsoft.com/en-us/research/wp-content/uploads/2016/12/Fitting-B-spline-Curves-to-Point-Clouds-by-Curvature-Based-Squared-Distance-Minimization.pdf

The input is a set of 2d points, the output are control points of a close cubic spline curve.

1. Input file: a file that contains n rows and each row reprents a point with x y positions.
2. Output files: a file with the control points of the output curve; and a file with sampling points of the output file. 

## Build instructions ##

This project depends on two code librarie:

1. Download Eigen e.g. 3.3.7 from http://eigen.tuxfamily.org/index.php?title=Main_Page, build and install the project into the dir ```EIGEN_DIR```
2. Download and extract ANN e.g. 1.1.2 to ANN_DIR from https://www.cs.umd.edu/~mount/ANN/
cd to the dir, and build: ```make linux-g++``` for linux (call ```make``` without parameters to see the build targets for different platforms).
3. Build the main project with cmake, set the cache variables ```EIGEN_DIR``` and ```ANN_DIR``` properly.
4. Build the python interface by navigating the ```py_interface``` dir in the build folder e.g. ```python setup.py install```.

Python example:

```python
import pysplfit
# Input point cloud in row-major format.
input = [0, 0, 0, 1, 1, 0, 1, 1]
# The control points and the contour in the same format. Only the first parameter is mandatory.
# alpha: curvature coeff, beta: curve length coeff, epsilon: stopping condition
fit_contorls, fit_contour = pysplfit.fit(input, controlnum=8, maxiternum=5, alpha=0.0025, beta=0.006, epsilon=0.002)

# see the demo.py
```

## Building and Running ##
Tested on Linux, however the original repo this code forked from targeted Windows...

I use cmake to configure and generate project files.

## Main Files ##
drawResult.m: a simple .m file to visulize the input and output

```core/cubic_b_spline.h```: a class encode the cubic b spline

```core/spline_curve_fitting.h```: 

```read_write_asc.h```: a simple class that reads/writes files

