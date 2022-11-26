#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<cmath>

using namespace std;

ofstream fout("output.txt");

void eline(double xin, double yin, double* X, double* Y, double* Q, const int N);

void efield(double x0, double y0, double* X, double* Y, double* Q, const int N, double& Ex, double& Ey);

void mdist(double x0, double y0, double* X, double* Y, const int N, double& rmin, double& rmax);

void eline(double xin, double yin, double* X, double* Y, double* Q, const int N) {
	const double step = 0.001;
	const double max_dist = 6.0;
	int i, direction;
	double x0, y0;
	double rmin, rmax, r, dx, dy, dl;
	double Ex, Ey, E;

	cout.precision(17);

	for (direction = -1; direction <= 1; direction += 2) {
		dl = direction * step;
		x0 = xin;
		y0 = yin;
		dx = 0.0;
		dy = 0.0;
		mdist(x0, y0, X, Y, N, rmin, rmax);
		while (rmin > 0.05 && rmax < max_dist) {
			fout << x0 << " " << y0 << '\n';
			efield(x0 + 0.5 * dx, y0 + 0.5 * dy, X, Y, Q, N, Ex, Ey);
			E = sqrt(Ex * Ex + Ey * Ey);
			if (E <= 1.0e-10) break;
			dx = dl * Ex / E;
			dy = dl * Ey / E;
			x0 = x0 + dx;
			y0 = y0 + dy;
			mdist(x0, y0, X, Y, N, rmin, rmax);
		}
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
	const double PI = 3.1415926;
	const int P = 20; 
	double X[P], Y[P], Q[P];
	int N;
	int i, j, nd;
	double x0, y0, theta;
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
	for (i = 0; i < N; i++) {
		for (j = 1; j <= (2 * nd); j++) {
			theta = (PI / nd) * j;
			x0 = X[i] + 0.1 * cos(theta);
			y0 = Y[i] + 0.1 * sin(theta);
			eline(x0, y0, X, Y, Q, N);
		}
	}
fout.close();
}

