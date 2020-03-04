cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(spline_fitting)

#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY )

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
add_executable(spline_fitting_test ${incs} ${srcs} read_write_asc.h read_write_asc.cpp main.cpp)
target_link_libraries(spline_fitting_test debug ANNd optimized ANN)

add_library(splfit SHARED ${incs} ${srcs} read_write_asc.h read_write_asc.cpp main.cpp)
set_property(TARGET splfit PROPERTY POSITION_INDEPENDENT_CODE ON)

# Copy the stuff needed for the python interface
add_custom_command(TARGET splfit PRE_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/py_interface)

set_target_properties(splfit PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/py_interface)
add_custom_command(TARGET splfit POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${ANN_DIR}/lib/libANN.a ${CMAKE_CURRENT_BINARY_DIR}/py_interface/libANN.a)

# TODO: add a loop/filelist or sth
add_custom_command(TARGET splfit POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/py_interface.h ${CMAKE_CURRENT_BINARY_DIR}/py_interface/py_interface.h)
add_custom_command(TARGET splfit POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/py_module.cpp ${CMAKE_CURRENT_BINARY_DIR}/py_interface/py_module.cpp)
add_custom_command(TARGET splfit POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/setup.py.in ${CMAKE_CURRENT_BINARY_DIR}/py_interface/setup.py)

