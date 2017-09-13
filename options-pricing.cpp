// options-pricing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <chrono>
#include <cmath>
#include <math.h>
#include <algorithm>
using namespace std;


int main(int argc, char* argv[])
{
	char option;
	float K;
	float T;
	float S0;
	float sigma;
	float r;
	float q;
	int N;
	char exercise;
	double price;
	clock_t time_before, time_after;
	float diff;
	double dt;
	double u, d;
	double **a;

	sscanf(argv[1], "%c", &option);
	sscanf(argv[2], "%f", &K);
	sscanf(argv[3], "%f", &T);
	sscanf(argv[4], "%f", &S0);
	sscanf(argv[5], "%f", &sigma);
	sscanf(argv[6], "%f", &r);
	sscanf(argv[7], "%f", &q);
	sscanf(argv[8], "%d", &N);
	sscanf(argv[9], "%c", &exercise);
	time_before = clock();

	a = new double* [N + 1];
	for (int i = 0; i < N + 1; ++i)
	{
		a[i] = new double[2];
	}

	dt = T / N;
	u = exp(sigma*sqrt(dt));
	d = exp(-sigma*sqrt(dt));
	double p_star = (exp((r-q)*dt)-d) / (u - d);
	
	if (option == 'C')
	{
		if (exercise == 'E')
		{
			for (int i = 0; i < N + 1; ++i)
			{
				a[i][0] = S0*(pow(u, N - i))*(pow(d, i));
				a[i][1] = fmax(a[i][0]-K,0);
			}
			for (int i = 0; i < N; ++i)
			{
				for (int j=0; j < (N - i); ++j)
				{
					a[j][1] = exp((-r*dt))*(p_star*a[j][1]+(1-p_star)*a[j+1][1]);
				}
			}
		}
		if (exercise == 'A')
		{
			for (int i = 0; i < N + 1; ++i)
			{
				a[i][0] = S0*(pow(u, N - i))*(pow(d, i));
				a[i][1] = fmax(a[i][0] - K, 0);
			}
			for (int i = 0; i < N; ++i)
			{
				for (int j=0; j < (N - i); ++j)
				{
					a[j][0]= S0*(pow(u, N-1-i-j))*(pow(d, j));
					a[j][1] = fmax(fmax((a[j][0] - K), 0), exp((-r*dt))*(p_star*a[j][1] + (1 - p_star)*a[j + 1][1]));
				}
			}
		}

	}
	if (option == 'P')
	{
		if (exercise == 'E')
		{
			for (int i = 0; i < N + 1; ++i)
			{
				a[i][0] = S0*(pow(u, N - i))*(pow(d, i));
				a[i][1] = fmax((K-a[i][0]), 0);
			}
			for (int i = 0; i < N; ++i)
			{
				for (int j = 0; j < (N - i); ++j)
				{
					a[j][1] = exp((-r*dt))*(p_star*a[j][1] + (1 - p_star)*a[j + 1][1]);
				}
			}
		}
		if (exercise == 'A')
		{
			for (int i = 0; i < N + 1; ++i)
			{
				a[i][0] = S0*(pow(u, N - i))*(pow(d, i));
				a[i][1] = fmax((K - a[i][0]), 0);
			}
			for (int i = 0; i < N; ++i)
			{
				for (int j = 0; j < (N - i); ++j)
				{
					a[j][0] = S0*(pow(u, N - 1 - i - j))*(pow(d, j));
					a[j][1] = fmax(fmax((K-a[j][0]), 0), exp((-r*dt))*(p_star*a[j][1] + (1 - p_star)*a[j + 1][1]));
				}
			}
		}
	}
	
	price = a[0][1];
	
	for (int i = 0; i < N + 1; ++i)
	{
		delete[] a[i];
	}
	delete[] a;
	time_after = clock();
	cout << "Option Price:" << price << endl;
	diff = ((double)time_after - (double)time_before) / CLOCKS_PER_SEC;
	cout << "Time Reqd:" << diff;

	return 0;
}

