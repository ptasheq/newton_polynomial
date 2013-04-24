#include "mathcore.h"
#include "translator.h"

using std::exception;

class DivByZeroException: public exception {
} divByZeroException;

class IdenticalNodesException: public exception {
} identicalNodesException;

Mathcore::~Mathcore() {
	delete intervalArithmetic;	
}

Mathcore & Mathcore::getInstance() {
	static Mathcore instance;
	return instance;
}

void Mathcore::divDifferences(uint, uint *, long double *) {
	/*for (uint i = 1; i <= n; ++i) {
		if (nodeValues[i-1] == nodeValues[i])
			throw identicalNodesException;
	}
	for (uint i = 1; i <= n; ++i) 
		for (uint j = n-i; j >=0; ++j)
				funcValues[j] = (funcValues[j+1] - funcValues[j]) / (nodeValues[j+1] - nodeValues[j]);*/
}

void Mathcore::newtonValue(const QString & str) {
	output->append("Newton value");		
}

void Mathcore::newtonCoeffs(const QString & str) {
	//if (Translator::getInstance().checkString(str))
		output->append("Newton coefficients");		
	output->append(str);
}

void Mathcore::setOutput(QTextEdit * output) {
	this->output = output;
}
