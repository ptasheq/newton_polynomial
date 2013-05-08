#include "mathcore.h"

using std::exception;

class DivByZeroException: public exception {
} divByZeroException;

class IdenticalNodesException: public exception {
} identicalNodesException;

Mathcore::Mathcore() {
	intervalValueArray = NULL;
	normalValueArray = NULL;
	nodeArray = NULL;
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

void Mathcore::divDifferences(uint n, int * nodeValues, interval * funcValues) {
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

void Mathcore::divDifferences(uint n, int * nodeValues, long double * funcValues) {
	if (n <= 1) {
		return;
	}
	for (uint i = 1; i < n; ++i) {
		if (nodeValues[i-1] == nodeValues[i])
			throw identicalNodesException;
	}
	int nodeDiff;
	for (uint i = n-1; i > 0; --i) 
		for (uint j = 0; j < i; ++j) {
			nodeDiff = nodeValues[j+n-i] - nodeValues[j];	
			funcValues[j] = (funcValues[j+1] - funcValues[j]) / nodeDiff;
		}
}

void Mathcore::newtonValue(const QString & str) {
	int n = translator->getNodeNumber(str);
	if (n > 0) {
		long double normalResult, normalBuf;
		interval intervalResult, intervalBuf;
		nodeArray = new int [n];
		intervalValueArray = new interval [n];
		normalValueArray = new long double [n];

		translator->stringToIntervals(intervalArithmetic, str, nodeArray, intervalValueArray);
		for (int i = 0; i < n; ++i) {
			normalValueArray[i] = (intervalValueArray[i].a + intervalValueArray[i].b)/2;
		}

		int node = QInputDialog::getInt(0, QString("Enter desired node"), QString("Node:"));
		divDifferences(n, nodeArray, normalValueArray);	
		divDifferences(n, nodeArray, intervalValueArray);
		normalResult = normalValueArray[0];
		intervalResult = intervalValueArray[0];
		for (int i = 1; i < n; ++i) {
			intervalBuf.a = intervalBuf.b = normalBuf =  node - nodeArray[i];
			intervalResult = intervalArithmetic->IAdd(intervalArithmetic->IMul(intervalResult, intervalBuf), intervalValueArray[i]); 	
			normalResult = normalResult * normalBuf + normalValueArray[i];
		}
		string a,b;
		intervalArithmetic->IEndsToStrings(intervalResult, a, b);
		output->append("Left headpoint:");
		output->append(a.c_str());
		output->append("Right headpoint:");
		output->append(b.c_str());
		output->append("Without interval arithmetic: ");
		std::cerr << normalResult;
		output->append(translator->getNumberAsQString(normalResult));
		delete [] nodeArray;
		delete [] intervalValueArray;
		delete [] normalValueArray;
	}
	else {
		output->append("error");
	}
}

void Mathcore::newtonCoeffs(const QString & str) {
	int n = translator->getNodeNumber(str);
	if (n > 0) {
		QString polynomial;
		nodeArray = new int [n];		
		intervalValueArray = new interval [n];
		interval xi;
		bool isNegative = false;

		translator->stringToIntervals(intervalArithmetic, str, nodeArray, intervalValueArray);
		divDifferences(n, nodeArray, intervalValueArray);
		for (int i = 1; i < n; ++i) {
			xi.a = xi.b = nodeArray[i];
			for (int j = i; j > 1; --j) {
				intervalValueArray[j] = intervalArithmetic->ISub(intervalValueArray[j], intervalArithmetic->IMul(intervalValueArray[j-1], xi));		
			}
		}
		string a,b;
		for (int i = 0; i < 2; ++i) {
			if (i == 0) {
				output->append("Left endpoints of intervals:");	
			}
			else {
				output->append("Right endpoints of intervals:");
			}
			string & number = (i == 0) ? a : b;
			polynomial.clear();
			for (int j = 0; j < n; ++j) {
				intervalArithmetic->IEndsToStrings(intervalValueArray[j], a, b);
				if (!isZero(number, number.size())) {
					if (number[0] == '-') {
						number.erase(0,1);
						isNegative = true;
					}
					if (!polynomial.isEmpty()) {
						polynomial += isNegative ? " - " : " + ";
					}
					polynomial += QString(number.c_str()) + translator->getExponentAsUnicode(n-j-1);
					isNegative = false;
				}
			}
			output->append(polynomial);
		}
		delete [] nodeArray;
		delete [] intervalValueArray;
	}
	else
		output->append("error");
}

void Mathcore::setOutput(QTextEdit * output) {
	this->output = output;
}
