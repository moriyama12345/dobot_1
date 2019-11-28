// 3階の常微分方程式をルンゲクッタ法で解く

#include <stdio.h>
#include <math.h>

#define N 101

double F0(double x, double y0, double y1, double y2);
double F1(double x, double y0, double y1, double y2);
double F2(double x, double y0, double y1, double y2); // ここに方程式


int main(void)
{
	int i;
	double e[N+1],h =0.1;
	double y0[N+1], y1[N+1], y2[N+1]; // y1は速度の無次元数
	double k1, k2, k3, k4;
	double l1, l2, l3, l4;
	double m1, m2, m3, m4;

	e[0] = 0.0;
	y0[0] = 0.0;
	y1[0] = 0.0;
	y2[0] = 0.33206; // 石川さんのデータ:0.33206

	for (i = 0; i < N; i++)
	{
		e[i + 1] = e[i] + h;

		k1 = h * F0(e[i], y0[i], y1[i], y2[i]);
		l1 = h * F1(e[i], y0[i], y1[i], y2[i]);
		m1 = h * F2(e[i], y0[i], y1[i], y2[i]);

		k2 = h * F0(e[i] + 0.5*h, y0[i] + 0.5*k1, y1[i] + 0.5*l1, y2[i] + 0.5*m1);
		l2 = h * F1(e[i] + 0.5*h, y0[i] + 0.5*k1, y1[i] + 0.5*l1, y2[i] + 0.5*m1);
		m2 = h * F2(e[i] + 0.5*h, y0[i] + 0.5*k1, y1[i] + 0.5*l1, y2[i] + 0.5*m1);

		k3 = h * F0(e[i] + 0.5*h, y0[i] + 0.5*k2, y1[i] + 0.5*l2, y2[i] + 0.5*m2);
		l3 = h * F1(e[i] + 0.5*h, y0[i] + 0.5*k2, y1[i] + 0.5*l2, y2[i] + 0.5*m2);
		m3 = h * F2(e[i] + 0.5*h, y0[i] + 0.5*k2, y1[i] + 0.5*l2, y2[i] + 0.5*m2);

		k4 = h * F0(e[i] + h, y0[i] + k3, y1[i] + l3, y2[i] + m3);
		l4 = h * F1(e[i] + h, y0[i] + k3, y1[i] + l3, y2[i] + m3);
		m4 = h * F2(e[i] + h, y0[i] + k3, y1[i] + l3, y2[i] + m3);

		y0[i + 1] = y0[i] + 1.0 / 6.0*(k1 + 2 * k2 + 2 * k3 + k4);
		y1[i + 1] = y1[i] + 1.0 / 6.0*(l1 + 2 * l2 + 2 * l3 + l4);
		y2[i + 1] = y2[i] + 1.0 / 6.0*(m1 + 2 * m2 + 2 * m3 + m4);
	}


	for (i = 0; i < N; i++)
	{
		printf("eta = %.1lf\t f = %lf\t f* = %lf\t f** = %lf\t f*** = %lf\n", e[i], y0[i], y1[i], y2[i], F2(e[i], y0[i], y1[i], y2[i]));
	}

	getchar();
	return 0;
}

double F0(double x, double y0, double y1, double y2)
{
	return y1;
}

double F1(double x, double y0, double y1, double y2)
{
	return y2;
}

double F2(double x, double y0, double y1, double y2)
{
	return -0.5*y0*y2;
}
