#include<iostream>
#include<fstream>
#include<vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <cmath> 
#include <iomanip> 
using std::upper_bound;
using namespace std;
ifstream fin("input.in");
ofstream fout("output.out");

int n, m, k;
vector<long double>x_values;
vector<vector<long double>>y_values;
vector<long double>points;
vector<vector<long double>>coefficients;
vector<long int>indexes;
long double alph, l, u, z, c, b, d;
// vector<double>::iterator low, up;
const int COEF = 10; // 10 - x, y, h, alph, l, u, z, c, b, d;

int main() {
	cin >> n;
	x_values.resize(n);
	coefficients.resize(n, vector<long double>(COEF));

	long double temp;
	for (int i = 0; i < n; i++)
	{
		cin >> temp;
		x_values[i] = temp;
		coefficients[i][0] = temp;
	}

	cin >> m;
	y_values.resize(m, vector<long double>(n));

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
		{
			cin >> temp;
			y_values[i][j] = temp;
			fout << temp << " ";
		}
		fout << endl;
	}

	cin >> k;
	//cout << k << " - this is k" << endl;
	points.resize(k);
	indexes.resize(k);
	for (int i = 0; i < k; i++)
	{
		cin >> temp;
		points[i] = temp;
	}


	// filling l, u, z, c, b ,d const values on border points

	coefficients[n - 1][3] = -1;
	coefficients[0][3] = -1;
	coefficients[n - 1][3] = -1;
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
			coefficients[i][6] = (coefficients[i][3] - coefficients[i - 1][2] * coefficients[i - 1][6])/coefficients[i][4];
		}


		// filling c, b, d
		for (int i = n - 2; i >= 0; i--)
		{
			coefficients[i][7] = (coefficients[i][6] - coefficients[i][5] * coefficients[i + 1][7]);
			coefficients[i][8] = ((coefficients[i + 1][1] - coefficients[i][1]) / coefficients[i][2]) - (coefficients[i][2] * (coefficients[i + 1][7] + 2 * coefficients[i][7]) / 3);
			coefficients[i][9] = (coefficients[i + 1][7] - coefficients[i][7]) / (3 * coefficients[i][2]);
		}
		coefficients[0][7] = (coefficients[0][6] - coefficients[0][5] * coefficients[1][7]);

		fout << endl;
		for (int i = 0; i < n; i++) {
			fout << setprecision(16) << " x is: " << coefficients[i][0] << " y is: " << coefficients[i][1] << " h is: " << coefficients[i][2] << " alph is: " << coefficients[i][3] << " l is: " << coefficients[i][4] << " u is: " << coefficients[i][5] << " z is: " << coefficients[i][6] <<
				" c is - " << coefficients[i][7] << " b is: " << coefficients[i][8] << " d is " << coefficients[i][9] << endl;
		}

		// finish completeion of y's set. Let's go to fiding values at control points

		int index_temp;
		for (int i = 0; i < k; i++)
		{
			auto up = upper_bound(x_values.begin(), x_values.end() - 1, points[i]);
			//cout << *up << " - YEEEEEY" << endl;
			auto idx = up - x_values.begin();
			int index_temp = (int)idx;
			/*cout << index_temp << "- index_temp" << endl;
			cout << x_values[i] << " " << temp << endl;*/
			index_temp--;

			cout << index_temp << endl;
			double difference = points[i] - coefficients[index_temp][0];
			//fout << difference << endl;
			fout << " This is point " << points[i] << " This is index " << index_temp << " This is difference " << difference<< endl;
			double res = coefficients[index_temp][1] + coefficients[index_temp][8] * difference +
				coefficients[index_temp][7] * pow(difference, 2) + coefficients[index_temp][9] * pow(difference, 3);
			fout <<"\n"<< setprecision(16) << res << "YEEEEEEAAAH,    ";
		}
		cout << endl << "NEW LINE: \n";

	}


	system("PAUSE");

}