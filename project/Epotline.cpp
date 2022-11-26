#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<cmath>

using namespace std;

ofstream fout("output.txt");

void epotline(double xin, double yin, double* X, double* Y, double* Q, const int N);

void efield(double x0, double y0, double* X, double* Y, double* Q, const int N, double& Ex, double& Ey);

void mdist(double x0, double y0, double* X, double* Y, const int N, double& rmin, double& rmax);

void epotline(double xin, double yin, double* X, double* Y, double* Q, const int N) {
	const double step = 0.02;
	const double max_dist = 5.0;
	int i;
	double x0, y0;
	double r, dx, dy, dl;
	double Ex, Ey, E;

	fout.precision(17);
	dl = step;
	x0 = xin;
	y0 = yin;
	dx = 0.0;
	dy = 0.0;
	r = step;
	while (r > (0.9 * dl) && r < max_dist) {
		fout << x0 << " " << y0 << endl;
		efield(x0 + 0.5 * dx, y0 + 0.5 * dy, X, Y, Q, N, Ex, Ey);
		E = sqrt(Ex * Ex + Ey * Ey);
		if (E <= 1.0e-10) break;
		dx = dl * Ey / E;
		dy = - dl * Ex / E;
		//if (dx < 1e-4 && dy < 1e-4) break;
		x0 = x0 + dx;
		y0 = y0 + dy;
		r = sqrt((x0 - xin) * (x0 - xin) + (y0 - yin) * (y0 - yin));
	}

}
void efield(double x0, double y0, double* X, double* Y, double* Q, const int N, double& Ex, double& Ey) {
	int i;
	double r3, xi, yi;
	Ex = 0.0;
	Ey = 0.0;
	for (i = 0; i < N; i++) {
		xi = x0 - X[i];
		yi = y0 - Y[i];
		r3 = pow(xi * xi + yi * yi, -1.5);
		Ex = Ex + Q[i] * xi * r3;
		Ey = Ey + Q[i] * yi * r3;
	}
}


void mdist(double x0, double y0, double* X, double* Y, const int N, double& rmin, double& rmax) {
	int i;
	double r;
	rmax = 0.0;
	rmin = 1000.0;
	for (i = 0; i < N; i++) {
		r = sqrt((x0 - X[i]) * (x0 - X[i]) + (y0 - Y[i]) * (y0 - Y[i]));
		if (r > rmax) rmax = r;
		if (r < rmin) rmin = r;
	}
}

int main() {
	string buf;
	const int P = 20;
	double X[P], Y[P], Q[P];
	int N;
	int i, j, nd;
	double x0, y0, rmin, rmax, L;
	cout << "Enter number of charges: " << endl;
	cin >> N;
	getline(cin, buf);
	cout << "N = " << N << endl;
	for (i = 0; i < N; i++) {
		cout << "Charge number " << i + 1 << endl;
		cout << "Position (X, Y) and charge (Q): " << endl;
		cin >> X[i] >> Y[i] >> Q[i];
		getline(cin, buf);
	}
	nd = 6; 
	L = 1.0;
	for (i = -nd; i <= nd; i++) {
		for (j = -nd; j <= nd; j++) {
			x0 = i * (L / nd);
			y0 = j * (L / nd);
			cout << i << " " << j << " " << x0 << " " << y0 << endl;
			mdist(x0, y0, X, Y, N, rmin, rmax);
			epotline(x0, y0, X, Y, Q, N);
		}

	}
fout.close();
}


