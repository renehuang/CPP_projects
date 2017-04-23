#include "pricer.h"

// FFT
dcmplx* FFT_simple(dcmplx* x, int N) {

	dcmplx* out = new dcmplx[N];
	dcmplx* scratch = new dcmplx[N];
	dcmplx* twiddles = FFT_get_twiddle_factors(N);

	FFT_calculate(x, N, 1, out, scratch, twiddles);

	delete[] twiddles;
	delete[] scratch;
	return out;

}

// IFFT
dcmplx* IFFT_simple(dcmplx* x, int N) {

	dcmplx* out = new dcmplx[N];
	dcmplx* scratch = new dcmplx[N];
	dcmplx* twiddles = FFT_get_twiddle_factors(N);

	FFT_calculate(x, N, 1, out, scratch, twiddles);

	delete[] twiddles;
	delete[] scratch;

	// Calculate IFFT via reciprocity property of DFT. 
	int N2 = N / 2;
	double tmp0, tmp1;
	out[0] = dcmplx(real(out[0]) / N, imag(out[0]) / N);
	out[N2] = dcmplx(real(out[N2]) / N, imag(out[N2]) / N);

	for (int i = 1; i<N2; i++) {
		tmp0 = real(out[i]) / N;
		tmp1 = imag(out[i]) / N;
		out[i] = dcmplx(real(out[N - i]) / N, imag(out[N - i]) / N);
		out[N - i] = dcmplx(tmp0, tmp1);
	}
	return out;

}

// Compute FFT
void FFT_calculate(dcmplx* x, int N, int skip, dcmplx* X, dcmplx* D, dcmplx* twiddles) {
	
	dcmplx * E = D + N / 2;
	int k;

	if (N == 1) {
		X[0] = x[0];
		return;
	}

	// use X as a scratch buffer 
	FFT_calculate(x, N / 2, skip * 2, E, X, twiddles);
	FFT_calculate(x + skip, N / 2, skip * 2, D, X, twiddles);

	for (k = 0; k < N / 2; k++) {
		D[k] = twiddles[k*skip] * D[k];
	}

	for (k = 0; k < N / 2; k++) {
		X[k] = E[k] + D[k];
		X[k + N / 2] = E[k] - D[k];
	}

}

// FFT twiddle factors
dcmplx* FFT_get_twiddle_factors(int N) {
	dcmplx* twiddles = new dcmplx[N / 2];
	int k;
	for (k = 0; k != N / 2; ++k) {
		twiddles[k] = exp(dcmplx(0, -2.0*PI*k / N));
	}
	return twiddles;
}

// Characteristic function
dcmplx optModifiedCFunc(dcmplx& v, double alpha, double s0, double r, double q, double t, double* param, charFuncOfLogOfStock logCF) {

	dcmplx IC(0.0, 1.0);
	dcmplx u = v - (alpha + 1.0)*IC;
	double u1 = exp(-r*t);
	dcmplx u2 = (*logCF)(u, s0, r, q, t, param);
	dcmplx u3 = (alpha + IC*v) * (alpha + IC*v + 1.0);

	return (u1*u2 / u3);

}


// FFT
double optPriceFFT(double alpha, double s0, double r, double q, double t, double eta, double k0, double* param, int N, charFuncOfLogOfStock logCF) {

	//double *price = new double[N];
	double *strike = new double[N];
	double lambda = 2.0 * PI / (N * eta);
	//double b = log(s0) -0.5*N*lambda;
	dcmplx *fftin = new dcmplx[N];
	double b = log(k0);

	for (int i = 0; i < N; ++i) {

		double j = i + 1.0;
		double vj_re = eta * (j - 1.0);
		double wj = eta / 3.*(3. + pow(-1., j));
		if (i == 0) wj = eta / 3.;

		dcmplx vj = dcmplx(vj_re, 0.0);
		dcmplx zz1 = optModifiedCFunc(vj, alpha, s0, r, q, t, param, logCF); // CF here
		dcmplx IC(0.0, -1.0);

		dcmplx fac = exp(IC*b*vj)*wj;
		fftin[i] = fac * zz1;

	}

	dcmplx *fftout = FFT_simple(fftin, N);

	/*
	for (int i = 0; i<N; ++i) {
		double k = b + lambda * i;
		strike[i] = exp(k);
		price[i] = exp(-alpha*k) / PI * fftout[i].real();
	}
	double p = price[0];
	*/
	
	double p = exp(-alpha * b) / PI * fftout[0].real();

	delete[] fftin;
	delete[] fftout;
	//delete[] price;
	delete[] strike;
	return p;

}

// Linear interpolation
double interpolate(double x1, double x2, double y1, double y2, double x) {
	double y = y1 + (x - x1) / (x2 - x1)*(y2 - y1);
	return y;
}

// Get price from FFT results
void getPrice(double *price, double *strike, std::vector<double>& p, std::vector<double>& k, int N) {
	// price and strike come out of FFT
	// p, k what we want for market strike

	std::cout << "Inside getPrice!" << std::endl;
	int j = 0;
	for (int j = 0; j < k.size(); j++) {
		
		int flag = 0;
		for (int i = 0; i < N - 1; ++i) {
			if ((strike[i] < k[j]) && (strike[i + 1] >= k[j])) {
				p.push_back(interpolate(strike[i], strike[i + 1], price[i], price[i + 1], k[j]));
				flag = 1;
				break;
			}
		}
		
		if (flag == 0) {
			p.push_back(std::numeric_limits<double>::quiet_NaN());
		}

	}
	
}

// Characteristic function VG
dcmplx charFuncOfLogOfStock_VG(dcmplx& u, double s0, double r, double q, double t, double* param) {

	// CF of Variance Gamma
	double sig = param[0];
	double v = param[1];
	double theta = param[2];

	dcmplx IC(0.0, 1.0);
	dcmplx a = IC*u*(log(s0) + (r - q + 1.0 / v*log(1.0 - sig*sig*v / 2.0 - theta*v))*t);
	dcmplx b = 1.0 / (1.0 - IC*u*theta*v + sig*sig*u*u*v / 2.0);
	dcmplx c = pow(b, t / v);
	return exp(a)*c;

}

// Characteristic function Heston
dcmplx charFuncOfLogOfStock_Heston(dcmplx& u, double s0, double r, double q, double t, double* param) {

}

// Characteristic function VGSA
dcmplx charFuncOfLogOfStock_VGSA(dcmplx& u, double s0, double r, double q, double t, double* param) {

}

// Characteristic function NIGSA
dcmplx charFuncOfLogOfStock_NIGSA(dcmplx& u, double s0, double r, double q, double t, double* param) {

}

// Characteristic function CGMYSA
dcmplx charFuncOfLogOfStock_CGMYSA(dcmplx& u, double s0, double r, double q, double t, double* param) {

}

// Characteristic function VGSSD
dcmplx charFuncOfLogOfStock_VGSSD(dcmplx& u, double s0, double r, double q, double t, double* param) {

}
