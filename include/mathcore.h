#ifndef MATHCORE_H
#define MATHCORE_H

#include "interval_arithmetic.h"

typedef unsigned int uint;

class Mathcore: public intervalarth::IntervalArithmetic {
	private:
		long double * valueArray;
		uint arraySize; 
		Mathcore() : valueArray(NULL), arraySize(0) {}
	public:
		~Mathcore() {}
		static Mathcore & getInstance();
		void divDifferences(uint, int *, long double *);
		long double newtonValue(uint, int *, long double *, int);
		void newtonCoeffs(uint, int *, long double *);
		void getValuesAsString(char *);
};

#endif

