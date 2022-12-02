#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<cmath>

using namespace std;

ofstream fout("output.txt");

const int L = 51;
const int xo = 20;
const int yo = 20;
const int h = 10;
const int l = 10;
bool isConductor[L][L];
double V[L][L];
double rho[L][L];

void initialize_lattice(const double& V1, const double& V2, const double& V3, const double& V4, const double& Q);
void laplace(const double& epsilon);


void initialize_lattice(const double& V1, const double& V2, const double& V3, const double& V4, const double& Q) {
	int Area;
	for (int i = 0; i < L; i++) {
		for (int j = 0; j < L; j++) {
			V[i][j] = 0.0;
			isConductor[i][j] = false;
			rho[i][j] = 0.0;
			//cout << i << j << endl;
		}
	}
	for (int i = 0; i < L; i++) {
		isConductor[0][i] = true;
		isConductor[i][0] = true;
		isConductor[L - 1][i] = true;
		isConductor[i][L - 1] = true;
		V[0][i] = V1;
		V[i][L - 1] = V2;
		V[L - 1][i] = V3;
		V[i][0] = V4;
		//cout << i << endl;
	}

	//cerr?

	Area = h * l;
	for (int i = xo; i <= (xo + l); i++) {
		for (int j = yo; j <= (yo + h); j++) {
			rho[i][j] = Q / Area;
			//cout << "area" << i << j << endl;
		}
	}
}

void laplace(const double& epsilon) {
	int icount = 0;
	double Vav, error, dV;
	while (icount < 10000) {
		icount++;
		error = 0.0;
		for (int i = 1; i < L - 1; i++) {
			for (int j = 1; j < L - 1; j++) {
				if (!isConductor[i][j]) {
					Vav = 0.25 * (V[i - 1][j] + V[i + 1][j] + V[i][j - 1] + V[i][j + 1] + rho[i][j]);
					dV = abs(V[i][j] - Vav);
					if (error < dV) error = dV;
					V[i][j] = Vav;
				}
			}
		}
		cout << icount << "err =" << error << endl;
		if (error < epsilon) return;
	}
	cerr << "Warning: laplace did not converge. \n";
}

int main() {
	string buf;
	double V1, V2, V3, V4, Q, epsilon;
	cout << "Enter V1, V2, V3, V4:" << endl;
	cin >> V1 >> V2 >> V3 >> V4; getline(cin, buf);
	cout << "Enter 4*Pi*Q:" << endl;
	cin >> Q; getline(cin, buf);
	cout << "Enter epsilon:" << endl;
	cin >> epsilon; getline(cin, buf);
	cout << "Starting Laplace:" << endl;
	cout << "Grid Size=" << L << endl;
	cout << "Conductors set at V1=" << V1 << endl << "V2=" << V2 << endl << "V3=" << V3 << endl << "V4=" << V4 << endl;
	cout << "Relaxing with accuracy epsilon=" << epsilon << endl;

	initialize_lattice(V1, V2, V3, V4, Q);
	laplace(epsilon);

	fout.precision(16);

	for (int i = 0; i < L; i++) {
		for (int j = 0; j < L; j++) {
			fout << i + 1 << " " << j + 1 << " " << V[i][j] << endl;
		}
	}
	fout.close();

}