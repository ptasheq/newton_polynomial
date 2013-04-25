#include "mathcore.h"
#include "translator.h"

using std::exception;

class DivByZeroException: public exception {
} divByZeroException;

class IdenticalNodesException: public exception {
} identicalNodesException;

Mathcore::Mathcore() {
	valueArray = NULL;
	nodeArray = 0;
	output = NULL;
	intervalArithmetic = new intervalarth::IntervalArithmetic();
	translator = new Translator();
}

Mathcore::~Mathcore() {
	delete intervalArithmetic;	
	delete translator;
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
	int n;
	if ((n = translator->getNodeNumber(str)) > 0) {
		nodeArray = new uint [n];		
		valueArray = new interval [n];
		translator->stringToIntervals(intervalArithmetic, str, nodeArray, valueArray);
		QString buf;
		string a, b;
		for (int i = 0; i < n; ++i) {
			intervalArithmetic->IEndsToStrings(valueArray[i], a, b);
			output->append(b.c_str());

		}
		delete nodeArray;
		delete valueArray;
	}
	else
		output->append("error");
}

void Mathcore::setOutput(QTextEdit * output) {
	this->output = output;
}
