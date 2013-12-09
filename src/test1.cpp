/*
 * test1.cpp
 *
 *  Created on: Dec 9, 2013
 *      Author: leal
 */

/******************************************************************************
 *
 * compile with : g++ -fopenmp openmp_test.cpp -o openmp_test
 *
 ******************************************************************************/
#include <omp.h>
#include <iostream>
#include <vector>

const unsigned int  N = 10000000;

// slow function
double invSqrt(double x) {
	static double xhalf = 0.5 * x;
	static int i = *(int*) &x;
	i = 0x5f3759df - (i >> 1);
	x = *(double*) &i;
	x = x * (1.5f - xhalf * x * x);
	return x;
}

int main_test1() {


	/* Fork a team of threads giving them their own copies of variables */
	#pragma omp parallel
	{
		// Obtain thread number
		int tid = omp_get_thread_num();

		//Only master thread does this
		if (tid == 0) {
			int nthreads = omp_get_num_threads();
			std::cout << "Master thread: number of threads = " << nthreads << std::endl;
		}
	}

	std::vector<double> vec(N);

	#pragma omp parallel for
	for (unsigned int i = 0; i < N; i++)
		vec[i] = invSqrt(i / 1.1);


	return 0;
}
