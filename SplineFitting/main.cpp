
#include "spline_curve_fitting.h"
#include "read_write_asc.h"
 
#include <iostream>
#include "py_interface.h"

// Expects float vector as input and returns a tuple of float arrays.
ResultTuple py_fit(std::vector<float> input, settings& s){

	CubicBSplineCurve curve(s.internal); 
	SplineCurveFitting scf;
	std::vector<Vector2d> points;
 
    int nCol = 2; // The number of columns is 2!  
	int nRow = input.size()/nCol;
	points.resize( nRow); 
	int idx = 0;
	for( int i = 0; i!= nRow; ++i)
	{ 
		points[i] = Vector2d( input[idx+0], input[idx+1]);
		idx += nCol;
	}

	scf.apply(points, curve, s.controlNum, s.maxIterNum, 
	    s.alpha, s.beta, s.epsilon, SPHERE_INIT);

    std::vector<float> controls;
    std::vector<float> contour;
    
    auto curve_controls = curve.getControls();
    auto curve_contour = curve.getSamples();
      
    for( int i = 0; i != curve_controls.size(); ++i){
		controls.push_back(curve_controls[i].x());
    	controls.push_back(curve_controls[i].y());
	}

    for( int i = 0; i != curve_contour.size(); ++i){
    	contour.push_back(curve_contour[i].x());
    	contour.push_back(curve_contour[i].y());
	}    
    
    ResultTuple t(controls, contour);
    return t;
}

// Python interface for the original app
void py_interface(char * input){
	string inFileName( input );
	string outFileName1 = inFileName + "_controls.txt";
	string outFileName2 = inFileName + "_spline.txt";

	CubicBSplineCurve curve(0.002);
	SplineCurveFitting scf;
 

	std::vector<Vector2d> points;
	CReadWriteAsc::readAsc( inFileName, points );

    settings s;
	scf.apply(points, curve, s.controlNum, s.maxIterNum, 
	    s.alpha, s.beta, s.epsilon, SPHERE_INIT);

//	CReadWriteAsc::writeAsc( inFileName, points);
	CReadWriteAsc::writeAsc( outFileName1, curve.getControls());
	CReadWriteAsc::writeAsc( outFileName2, curve.getSamples() );
}

int main(int argc, char *argv[])
{

	char inpf[200],*input; 
	argc--;argv++;					//Skip program name arg

	if (argc<1)
	{
		cout<<"Input file:"<<endl;
		cin>>inpf; 
		input = inpf;
	}
	else input    = argv[0];

    py_interface(input);

}
