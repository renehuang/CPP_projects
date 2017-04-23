#ifndef __OBJFUNC_H__
#define __OBJFUNC_H__
#include "pricer.h"

// using FFT for each option
// eta = 0.5, N = 2^6

class ObjFunc {

public:

	ObjFunc();
	double evalObjFunc(double* v, const ObjFuncInput& input);
	void getPrice(double* v, const ObjFuncInput& input, std::vector<double>& price);
	~ObjFunc();

};

#endif