#include "mathcore.h"

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

void Mathcore::divDifferences(uint n, uint * nodeValues, interval * funcValues) {
	if (n <= 1) {
		return;
	}
	for (uint i = 1; i < n; ++i) {
		if (nodeValues[i-1] == nodeValues[i])
			throw identicalNodesException;
	}
	interval nodeDiff;
	for (uint i = n-1; i > 0; --i) 
		for (uint j = 0; j < i; ++j) {
			nodeDiff.a = nodeDiff.b = nodeValues[j+n-i] - nodeValues[j];	
			funcValues[j] = intervalArithmetic->IDiv(intervalArithmetic->ISub(funcValues[j+1], funcValues[j]), nodeDiff); 
		}
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
		string a, b;
		divDifferences(n, nodeArray, valueArray);
		for (int i = 0; i < n; ++i) {

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
