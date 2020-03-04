BSplineFitting
==============

Fitting cubic spline curve to 2d points (with Python interface)

## Introduction ##

This is an implementation of paper "Fitting B-spline Curves to Point Clouds
by Curvature-Based Squared Distance Minimization".

Link to the paper: [http://www.geometrie.tuwien.ac.at/ig/sn/2006/wpl\_curves\_06/wpl\_curves\_06.html](http://www.geometrie.tuwien.ac.at/ig/sn/2006/wpl_curves_06/wpl_curves_06.html "link")

The input is a set of 2d points, the output are control points of a close cubic spline curve.

1. Input file: a file that contains n rows and each row reprents a point with x y positions.
2. Output files: a file with the control points of the output curve; and a file with sampling points of the output file. 

## Build instructions ##

This project depends on two code librarie:

1. Download Eigen e.g. 3.3.7 from http://eigen.tuxfamily.org/index.php?title=Main\_Page, build and install the project into the dir ```EIGEN_DIR```
2. Download and extract ANN e.g. 1.1.2 to ANN_DIR from https://www.cs.umd.edu/~mount/ANN/
cd to the dir, and build: ```make linux-g++``` for linux (call ```make``` without parameters to see the build targets for different platforms).
3. Build the main project with cmake, set the cache variables ```EIGEN_DIR``` and ```ANN_DIR``` properly.
4. Build the python interface by navigating the ```py_interface``` dir. Add the libs to the path before using.

## Building and Running ##
BSplineFitting should be able to run in any environment, but it is **only** tested in windows enviroment.

I use cmake to configure and generate project files.

## Main Files ##
drawResult.m: a simple .m file to visulize the input and output

```core/cubic_b_spline.h```: a class encode the cubic b spline

```core/spline_curve_fitting.h```: 

```read_write_asc.h```: a simple class that reads/writes files







