#include "ObjFunc.h"

using namespace std;

ObjFunc::ObjFunc() {}

ObjFunc::~ObjFunc() {}

double ObjFunc::evalObjFunc(double* v, const ObjFuncInput& input) {

	double alpha = input.alpha;
	double eta = input.eta;
	int pow2 = input.N;
	double N = pow(2, pow2);

	double* S = input.S;
	double* K = input.K;
	double* T = input.T;
	double* r = input.r;
	double* q = input.q;
	double* p = input.p;
	double* callPut = input.callPut;
	double* w = input.w;
	int n = input.n;

	double objFun = 0.0;
	for (int i = 0; i < n; i++) {
		
		double pModel = optPriceFFT(callPut[i] * alpha, S[i], r[i], q[i], T[i], eta, K[i], v, N, &charFuncOfLogOfStock_VG);

	}
	
	return objFun;

}

void ObjFunc::getPrice(double* v, const ObjFuncInput& input, std::vector<double>& price) {

	double alpha = input.alpha;
	double eta = input.eta;
	int pow2 = input.N;
	double N = pow(2, pow2);

	double* S = input.S;
	double* K = input.K;
	double* T = input.T;
	double* r = input.r;
	double* q = input.q;
	double* p = input.p;
	double* callPut = input.callPut;
	double* w = input.w;
	int n = input.n;

	double* param = v;
	for (int i = 0; i < n; i++) {
		double pModel = optPriceFFT(callPut[i] * alpha, S[i], r[i], q[i], T[i], eta, K[i], v, N, &charFuncOfLogOfStock_VG);
		price.push_back(pModel);
	}
	
}