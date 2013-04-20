#include "mathcore.h"

using std::exception;

class DivByZeroException: public exception {
} divByZeroException;

class IdenticalNodesException: public exception {
} identicalNodesException;

Mathcore & Mathcore::getInstance() {
	static Mathcore instance;
	return instance;
}

void Mathcore::divDifferences(uint n, int * nodeValues, long double * funcValues) {
	for (uint i = 1; i <= n; ++i) {
		if (nodeValues[i-1] == nodeValues[i])
			throw identicalNodesException;
	}
	for (uint i = 1; i <= n; ++i) 
		for (uint j = n-i; j >=0; ++j)
				funcValues[j] = (funcValues[j+1] - funcValues[j]) / (nodeValues[j+1] - nodeValues[j]);
}

long double Mathcore::newtonValue(uint n, int * nodeArray, long double * diffArray, int point) {
		
	return 0.0;
}

void Mathcore::newtonCoeffs(uint n, int * nodeArray, long double * diffArray) {

}
