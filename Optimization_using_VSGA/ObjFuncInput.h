#pragma once
#ifndef __OBJFUNCINPUT_H__
#define __OBJFUNCINPUT_H__

#include <iostream>
#include <vector>

// Define the objective function input params
struct ObjFuncInput {

	// Option params
	int n;
	double* S;
	double* K;
	double* T;
	double* r;
	double* q;
	double* p;
	double* callPut; // 1 for call, -1 for put
	double* w;
	
	// FFT params
	double alpha;
	double eta;
	double N;  // 2 to the power of N

};



#endif // !__OBJFUNCINPUT_H__

