cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(spline_fitting)

set(CMAKE_CXX_STANDARD 11)

# Eigen
set(EIGEN_DIR CACHE FILEPATH "Eigen (install) directory")
include_directories(${EIGEN_DIR}/include/eigen3)

# ANN
set(ANN_DIR CACHE FILEPATH "ANN root directory" )
include_directories(${ANN_DIR}/include)
link_directories(${ANN_DIR}/lib)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/core)
set(incs core/cubic_b_spline.h core/spline_curve_fitting.h)
set(srcs core/cubic_b_spline.cpp core/spline_curve_fitting.cpp)
add_executable(spline_fitting_test ${incs} ${srcs} read_write_asc.h read_write_asc.cpp main.cpp )
target_link_libraries(spline_fitting_test debug ANNd optimized ANN)
