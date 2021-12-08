#include<bits/stdc++.h>
using namespace std;

//温度
const double T = 1;

//計算範囲
const double g_max = 1000;

//計算精度
const double threshold = 1e-3; //p<thresholdの領域を無視
const double dx = 1e-3;
const double dg = 1e-1;

//期待値
double E(double g, function<double(double)> f) {
	double nmr = 0;	//分子
	double dnm = 0;	//分母

	// x in [0,infty)
	for (double x = 0;; x += dx) {
		double p = exp(-g / 4 * x * x * x * x + g / 2 * x * x);
		if (p < threshold)
			break;
		nmr += p * f(x) * dx;
		dnm += p * dx;
	}

	// x in (-infty,0)
	for (double x = -dx;; x -= dx) {
		double p = exp(-g / 4 * x * x * x * x + g / 2 * x * x);
		if (p < threshold)
			break;
		nmr += p * f(x) * dx;
		dnm += p * dx;
	}

	return nmr / dnm;
}

int main() {
	//出力ファイル
	ofstream out("output.txt");

	//g in (0,g_max]
	for (double g = dg; g <= g_max; g += dg) {

		//exp(-g * T * x * x)の期待値
		double v = E(g, [g](double x) {
			return exp(-g * T * x * x);
		});

		//出力
		out << g << "\t" << v * exp(T) << endl;
	}
}
