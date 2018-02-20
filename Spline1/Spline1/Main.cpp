#include<iostream>
#include<fstream>
#include<vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <functional> 
using std::upper_bound;
using std::lower_bound;
using namespace std;
ifstream fin("input.in");
ofstream fout("output.out");

int n, m, k;
vector<double>x_values;
vector<vector<double>>y_values;
vector<double>points;
vector<vector<double>>coefficients;
double alph, l, u, z, c, b, d;
vector<double>::iterator low, up;
const int COEF = 10; // 10 - x, y, h, alph, l, u, z, c, b, d;

int main() {
	fin >> n;
	x_values.resize(n);
	coefficients.resize(n, vector<double>(COEF));

	double temp;
	for (int i = 0; i < n; i++)
	{
		fin >> temp;
		x_values[i] = temp;
		coefficients[i][0] = temp;
	}

	up = upper_bound(x_values.begin(), x_values.end() - 1, 0.9);
	low = lower_bound(x_values.begin(), x_values.end() - 1, 0.9);
	cout << *up << "YEEEEEY" << endl;
	cout << *low << "kkkkkk";
	auto idx = low - x_values.begin();
	int index = (int)idx;
	cout << index << "INDEX" << endl;

	fin >> m;
	y_values.resize(m, vector<double>(n));

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			fin >> temp;
			y_values[i][j] = temp;
		}

	fin >> k;
	cout << k;
	points.resize(k);

	// filling l, u, z, c, b ,d const values on border points
	coefficients[0][4] = 1;
	coefficients[n - 1][4] = 1;
	coefficients[0][5] = 0;
	coefficients[n - 1][5] = -1;
	coefficients[0][6] = 0;
	coefficients[n - 1][6] = 0;
	coefficients[0][7] = 0;
	coefficients[n - 1][7] = 0;
	coefficients[n - 1][8] = -1;
	coefficients[n - 1][9] = -1;


	for (int j = 0; j < m; j++)
	{
		for (int i = 0; i < n; i++)
		{
			coefficients[i][1] = y_values[j][i];

		}

		// filling h values
		for (int i = 0; i < n - 1; i++) {
			coefficients[i][2] = x_values[i + 1] - x_values[i];
			coefficients[i][2] = x_values[i + 1] - x_values[i];
		}
		coefficients[n - 1][2] = -1;

		// filling alph values
		coefficients[0][3] = -1;
		coefficients[n - 1][3] = -1;


		for (int i = 1; i < n - 1; i++) {
			coefficients[i][3] = (3 * (coefficients[i + 1][1] - coefficients[i][1]) / coefficients[i][2]) - (3 * (coefficients[i][1] - coefficients[i - 1][1]) / coefficients[i - 1][2]);
		}


		// filling l, u, z
		for (int i = 1; i < n - 1; i++) {
			coefficients[i][4] = 2 * (coefficients[i + 1][0] - coefficients[i - 1][0]) - coefficients[i - 1][2] * coefficients[i - 1][5];
			coefficients[i][5] = coefficients[i][2] / coefficients[i][4];
			coefficients[i][6] = (coefficients[i][1] - coefficients[i - 1][2] * coefficients[i - 1][6]);
		}

		// filling c, b, d
		for (int i = n - 2; i > 0; i--)
		{
			coefficients[i][7] = (coefficients[i][6] - coefficients[i][5] * coefficients[i + 1][7]);
			coefficients[i][8] = (coefficients[i + 1][1] - coefficients[i][1]) / coefficients[i][2] - coefficients[i][2] * (coefficients[i + 1][7] + 2 * coefficients[i][7]) / 3;
			coefficients[i][9] = (coefficients[i + 1][7] - coefficients[i][7]) / (3 * coefficients[i][2]);
		}
		coefficients[0][7] = (coefficients[0][6] - coefficients[0][5] * coefficients[1][7]);


	}




	/*
	for (int i = 0; i < k; i++)
	{
	cout << "Flag";
	fin >> temp;
	points[i] = temp;
	}



	fout << n << " " << m << " "<< k << endl;
	for (int i = 0; i < n; i++)
	{
	fout << x_values[i] << " ";
	}*/




	system("PAUSE");
}
