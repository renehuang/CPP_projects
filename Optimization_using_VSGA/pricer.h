#ifndef __PRICER_H__
#define __PRICER_H__

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <ctime>
#include <map>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <complex>
// #include "tgmath.h"
#include "ObjFuncInput.h"
//#include "characterFunc.h"


//typedef double(*penaltyFunction)(double, double, double);

#define PI  3.1415926535897932

// Types definition
typedef std::complex<double> dcmplx;
typedef dcmplx(*charFuncOfLogOfStock)(dcmplx&, double, double, double, double, double*);

dcmplx* FFT_simple(dcmplx*, int);
dcmplx* IFFT_simple(dcmplx*, int);
void FFT_calculate(dcmplx*, int, int, dcmplx*, dcmplx*, dcmplx*);
dcmplx* FFT_get_twiddle_factors(int);

dcmplx charFuncOfLogOfStock_VG(dcmplx& u, double s0, double r, double q, double t, double* param);
dcmplx charFuncOfLogOfStock_Heston(dcmplx& u, double s0, double r, double q, double t, double* param);
dcmplx charFuncOfLogOfStock_VGSA(dcmplx& u, double s0, double r, double q, double t, double* param);
dcmplx charFuncOfLogOfStock_NIGSA(dcmplx& u, double s0, double r, double q, double t, double* param);
dcmplx charFuncOfLogOfStock_CGMYSA(dcmplx& u, double s0, double r, double q, double t, double* param);
dcmplx charFuncOfLogOfStock_VGSSD(dcmplx& u, double s0, double r, double q, double t, double* param);

dcmplx optModifiedCFunc(dcmplx&, double, double, double, double, double, double*, charFuncOfLogOfStock);
double optPriceFFT(double, double, double, double, double, double, double, double*, int, charFuncOfLogOfStock);

double interpolate(double, double, double, double, double);
void getPrice(double*, double*, std::vector<double>&, std::vector<double>&, int);

#endif