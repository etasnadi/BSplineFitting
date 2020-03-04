
#include "spline_curve_fitting.h"
#include "read_write_asc.h"

#include <iostream>
#include "py_interface.h"

// Expects float vector as input and returns a tuple of float arrays.
ResultTuple py_fit(std::vector<float> input, int nCol){

	CubicBSplineCurve curve(0.002);
	SplineCurveFitting scf;
	std::vector<Vector2d> points;

	int nRow = input.size()/nCol;
	points.resize( nRow);
	int idx = 0;
	for( int i = 0; i!= nRow; ++i )
	{
		points[i] = Vector2d( input[idx+0], input[idx+1]);
		idx += nCol;
	}
	
	scf.apply(points, curve, 28, 50, 0.005, 0.005, 0.0001, SPHERE_INIT);

    std::vector<float> controls;
    std::vector<float> contour;
    
    auto ctrl = curve.getControls();
    auto samples = curve.getSamples();
    
    for( int i = 0; i!= ctrl.size(); ++i){
		controls.push_back(ctrl[i].x());
    	controls.push_back(ctrl[i].y());
		contour.push_back(samples[i].x());
    	contour.push_back(samples[i].y());
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

	scf.apply(points, curve, 28, 50, 0.005, 0.005, 0.0001, SPHERE_INIT);

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
