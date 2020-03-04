#include "read_write_asc.h"

#include <fstream>
#include <iostream>

//
std::vector<double> read_data(const string& filename, int &nRow, int &nCol){
	std::ifstream fin(filename);
	std::vector<double> coefficients;

	std::string line;
	nRow = 0;
	nCol = 0;
	if( !fin.fail() ){
	    while( std::getline( fin, line ) )
	    {
		    std::stringstream ss(line);
		    double d = 0;
		    nCol = 0;
		    while( ss >> d)
		    {
			    coefficients.push_back( d);
			    ++nCol;
		    }
		    ++nRow;
	    }
	    fin.close();
	}
	return coefficients;
}		

bool constructFromArr(float *arr, vector<Vector2d>& points, int nRow, int nCol){	
	points.resize( nRow);
	int idx = 0;
	for( int i = 0; i!= nRow; ++i )
	{
		points[i] = Vector2d( arr[idx+0], arr[idx+1]);
		idx += nCol;
	}
}

float* getResult(){

}

bool CReadWriteAsc::readAsc( const string& filename, vector<Vector2d>& points )
{

    std::vector<double> coefficients;
    int nRow = 0;
    int nCol = 0;
    
    coefficients = read_data(filename, nRow, nCol);
	
	points.resize( nRow);
	int idx = 0;
	for( int i = 0; i!= nRow; ++i )
	{
		points[i] = Vector2d( coefficients[idx+0], coefficients[idx+1]);
		idx += nCol;
	}
	return true;
}



bool CReadWriteAsc::writeAsc( const string& filename, const vector<Vector2d>& points )
{
	ofstream fout( filename.c_str());
	if( fout.fail() )
		return false;

	for( int i = 0; i!= points.size(); ++i )
	{
		fout << points[i].x() << " " << points[i].y()  << " 0" << endl;
	}
	fout.close();

	return true;

}
