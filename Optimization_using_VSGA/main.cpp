#include "Simplex.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Read the csv file
bool readCSV(string inputFileName, double* S, double* K, double* T, double* r, double* q, double* p, double *callPut, double* w, int n) {

}

int main() {

	int n = 27;
	double* S = new double[n];
	double* K = new double[n];
	double* T = new double[n];
	double* r = new double[n];
	double* q = new double[n];
	double* p = new double[n];
	double* callPut = new double[n];
	double* w = new double[n];

	std::cout << "Input data" << endl;
	std::cout << "S,T,K,r,q,price,callPut" << endl;
	string inputFileName;
	readCSV(inputFileName, S, K, T, r, q, p, callPut, w, n);
	std::cout << endl;
	
	ObjFuncInput input;
	input.n = n;
	input.S = S;
	input.K = K;
	input.T = T;
	input.r = r;
	input.q = q;
	input.p = p;
	input.callPut = callPut;
	input.w = w;

	input.alpha = 1.5;
	input.eta = 0.25;
	input.N = 7;
	
	ObjFunc objf = ObjFunc();
	OptimSet optimSet = { 1000, 1000, 1e-08 };
	
	vector<double> start = { };
	double rmse = nelderMead(start, optimSet, objf, input);

	delete[] S;
	delete[] K;
	delete[] T;
	delete[] r;
	delete[] q;
	delete[] p;
	delete[] callPut;
	delete[] w;

}