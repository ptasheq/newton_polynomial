#include "mathcore.h"

Mathcore::Mathcore() {
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

short Mathcore::divDifferences(uint n, long double * nodeValues, interval * funcValues) {
	if (n <= 1) {
		return TOO_FEW_NODES;
	}
	for (uint i = 1; i < n; ++i) {
		if (nodeValues[i-1] == nodeValues[i])
			return IDENTICAL_NODES;
	}
	interval nodeDiff;
	for (uint i = n-1; i > 0; --i) 
		for (uint j = 0; j < i; ++j) {
			nodeDiff.a = nodeDiff.b = nodeValues[j+n-i] - nodeValues[j];	
			funcValues[j] = intervalArithmetic->IDiv(intervalArithmetic->ISub(funcValues[j+1], funcValues[j]), nodeDiff); 
		}
	return SUCCESS;
}

short Mathcore::divDifferences(uint n, long double * nodeValues, long double * funcValues) {
	if (n <= 1) {
		return TOO_FEW_NODES;
	}
	for (uint i = 1; i < n; ++i) {
		if (nodeValues[i-1] == nodeValues[i])
			return IDENTICAL_NODES;
	}
	long double nodeDiff;
	for (uint i = n-1; i > 0; --i) 
		for (uint j = 0; j < i; ++j) {
			nodeDiff = nodeValues[j+n-i] - nodeValues[j];
			funcValues[j] = (funcValues[j+1] - funcValues[j]) / nodeDiff;
		}
	return SUCCESS;
}

void Mathcore::newtonValue(const QString & str) {
	int n = translator->getNodeNumber(str);
	if (n > 0) {
		long double normalResult;
		short errorFlag;
		interval intervalResult;
		long double * nodeArray = new long double [n];
		interval * intervalValueArray = new interval [n];
		long double * normalValueArray = new long double [n];

		translator->stringToIntervals(intervalArithmetic, str, nodeArray, intervalValueArray);
		for (int i = 0; i < n; ++i) {
			normalValueArray[i] = (intervalValueArray[i].a + intervalValueArray[i].b)/2;
		}

		long double node = QInputDialog::getDouble(0, QString("Enter desired node"), QString("Node:"));
		if ((errorFlag = divDifferences(n, nodeArray, normalValueArray))  != SUCCESS
		|| (errorFlag = divDifferences(n, nodeArray, intervalValueArray)) != SUCCESS) {
			switch (errorFlag) {
				case TOO_FEW_NODES:
					output->append("Error: too few nodes!");
					break;
				case DIV_BY_ZERO:
					output->append("Error: division by zero!");
					break;
				default:
					output->append("Error: identical node values!");
			}
			return;
		}
		intervalResult = newtonVal(intervalArithmetic, n, node, nodeArray, intervalValueArray);
		normalResult = newtonVal(n, node, nodeArray, normalValueArray);
		string a,b;
		intervalArithmetic->IEndsToStrings(intervalResult, a, b);
		output->append("Left headpoint:");
		output->append(a.c_str());
		output->append("Right headpoint:");
		output->append(b.c_str());
		output->append("Without interval arithmetic: ");
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
		QString polynomial, polynomialNormal;
		long double * nodeArray = new long double [n];		
		interval * intervalValueArray = new interval [n];
		long double * normalValueArray = new long double [n];
		bool isNegative = false;
		short errorFlag;
		interval xi;

		translator->stringToIntervals(intervalArithmetic, str, nodeArray, intervalValueArray);
		for (int i = 0; i < n; ++i) {
			normalValueArray[i] = (intervalValueArray[i].a + intervalValueArray[i].b)/2;
		}
		if ((errorFlag = divDifferences(n, nodeArray, normalValueArray))  != SUCCESS
		|| (errorFlag = divDifferences(n, nodeArray, intervalValueArray)) != SUCCESS) {
			switch (errorFlag) {
				case TOO_FEW_NODES:
					output->append("Error: too few nodes!");
					break;
				case DIV_BY_ZERO:
					output->append("Error: division by zero!");
					break;
				default:
					output->append("Error: identical node values!");
			}
			return;
		}
		newtonCoeff(intervalArithmetic, n, nodeArray, intervalValueArray);
		newtonCoeff(n, nodeArray, normalValueArray);
		string a,b;
		for (int i = 0; i < 2; ++i) {
			string & number = (i == 0) ? a : b;
			polynomial.clear();
			for (int j = 0; j < n; ++j) {
				if (i == 0 && normalValueArray[j] != 0.0) {
					xi.a = xi.b = normalValueArray[j];
					intervalArithmetic->IEndsToStrings(xi, b, b);
					if (b[0] == '-') {
						b.erase(0,1);
						isNegative = true;
					}
					if (!polynomialNormal.isEmpty()) {
						polynomialNormal += isNegative ? " - " : " + ";
					}
					polynomialNormal += QString(b.c_str()) + translator->getExponentAsUnicode(n-j-1);
					isNegative = false;
				}
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
			if (i == 0) {
				output->append("Without interval arithmetic:");
				output->append(polynomialNormal);
				output->append("Left endpoints of intervals:");	
			}
			else {
				output->append("Right endpoints of intervals:");
			}
			output->append(polynomial);
		}
		delete [] nodeArray;
		delete [] intervalValueArray;
		delete [] normalValueArray;
	}
	else
		output->append("error");
}

void Mathcore::setOutput(QTextEdit * output) {
	this->output = output;
}

interval newtonVal(IntervalArithmetic * ia, uint n, long double node, long double * nodeArray, interval * valueArray) {
	
	interval buf, result = valueArray[0];
	for (uint i = 1; i < n; ++i) {
		buf.a = buf.b = node - nodeArray[i];
		result = ia->IAdd(ia->IMul(result, buf), valueArray[i]);
	}
	return result;
}

long double newtonVal(uint n, long double node, long double * nodeArray, long double * valueArray) {

	long double result = valueArray[0];
	for (uint i = 1; i < n; ++i) {
		result = result * (node - nodeArray[i]) + valueArray[i];
	}
	return result;
}

void newtonCoeff(IntervalArithmetic * ia, uint n, long double * nodeArray, interval * valueArray) {

	interval xi;
	for (uint i = 1; i < n; ++i) {
		xi.a = xi.b = nodeArray[i];
		for (uint j = i; j > 1; --j) {
			valueArray[j] = ia->ISub(valueArray[j], ia->IMul(valueArray[j-1], xi));
		}
	}
}

void newtonCoeff(uint n, long double * nodeArray, long double * valueArray) {

	for (uint i = 1; i < n; ++i) {
		for (uint j = i; j > 1; --j) {
			valueArray[j] = valueArray[j] - valueArray[j-1] * nodeArray[i];
		}
	}
}
