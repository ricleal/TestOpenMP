/*
 * test2.cpp
 *
 *  Created on: Dec 9, 2013
 *      Author: leal
 */

#include <iostream>

#include <stdlib.h>
#include <omp.h>

#define N  20
#define CHUNKSIZE   5

int main_test2() {

	int i, chunk, tid;
	double in[N], out[N];
	char first_time;

	/* Some initializations */
	for (i = 0; i < N; i++)
		in[i] = i;

	chunk = CHUNKSIZE;
	first_time = 'y';

	omp_set_num_threads(2);

	#pragma omp parallel for     \
		shared(in,out,chunk)        \
  	  	private(i,tid)             \
  	  	schedule(static,chunk)     \
  	  	firstprivate(first_time)

	for (i = 0; i < N; i++) {
		if (first_time == 'y') {
			tid = omp_get_thread_num();
			first_time = 'n';
			#pragma omp critical
			std::cout << "First time : tid = " <<tid << " :: i = " << i << " :: outi] = " << out[i] << std::endl;
		}
		out[i] = in[i];
		#pragma omp critical
		std::cout << "tid = " <<tid << " :: i = " << i << " :: out[i] = " << out[i] << std::endl;
	}

	return 0;
}
