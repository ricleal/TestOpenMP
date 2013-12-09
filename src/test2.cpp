/*
 * test2.cpp
 *
 *  Created on: Dec 9, 2013
 *      Author: leal
 */

#include <iostream>

#include <stdlib.h>
#include <omp.h>

#define N       50
#define CHUNKSIZE   5

int main_test2() {

	int i, chunk, tid;
	double a[N], b[N], c[N];
	char first_time;

	/* Some initializations */
	for (i = 0; i < N; i++)
		a[i] = b[i] = i * 1.0;

	chunk = CHUNKSIZE;
	first_time = 'y';

	omp_set_num_threads(4);

	#pragma omp parallel for     \
		shared(a,b,c,chunk)        \
  	  	private(i,tid)             \
  	  	schedule(static,chunk)     \
  	  	firstprivate(first_time)

	for (i = 0; i < N; i++) {
		if (first_time == 'y') {
			tid = omp_get_thread_num();
			first_time = 'n';
			#pragma omp critical
			std::cout << "First time : tid = " <<tid << " :: i = " << i << " :: c[i] = " << c[i] << std::endl;
		}
		c[i] = a[i] + b[i];
		#pragma omp critical
		std::cout << "tid = " <<tid << " :: i = " << i << " :: c[i] = " << c[i] << std::endl;
	}

	return 0;
}
