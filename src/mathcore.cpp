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

short Mathcore::divDifferences(uint n, interval * nodeValues, interval * funcValues) {
	if (n <= 1) {
		return TOO_FEW_NODES;
	}
	for (uint i = 1; i < n; ++i) {
		if (nodeValues[i-1].a + nodeValues[i-1].b == nodeValues[i].a + nodeValues[i].b)
			return IDENTICAL_NODES;
	}
	interval nodeDiff;
	for (uint i = n-1; i > 0; --i) {
		for (uint j = 0; j < i; ++j) {
			nodeDiff = intervalArithmetic->ISub(nodeValues[j+n-i], nodeValues[j]);	
			funcValues[j] = intervalArithmetic->IDiv(intervalArithmetic->ISub(funcValues[j+1], funcValues[j]), nodeDiff); 
		}
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
	bool intervalOnlyFlag = false;
	int n = translator->getNodeNumber(str, intervalOnlyFlag);
	if (n > 0) {
		long double normalResult;
		short errorFlag;
		interval intervalNode, intervalResult;
		long double * nodeArray = new long double [n];
		interval * intervalNodeArray = new interval [n];
		interval * intervalValueArray = new interval [n];
		long double * normalValueArray = new long double [n];

		translator->stringToIntervals(intervalArithmetic, str, intervalNodeArray, intervalValueArray);
		for (int i = 0; i < n; ++i) {
			normalValueArray[i] = (intervalValueArray[i].a + intervalValueArray[i].b)/2;
			nodeArray[i] = (intervalNodeArray[i].a + intervalNodeArray[i].b)/2;
		}

		if ((intervalNode = translator->getNodeFromDialog(intervalArithmetic, intervalOnlyFlag)).a == 0 &&
			intervalNode.b == 0) {
			output->append("Error");
			return;
		}
		if ((errorFlag = divDifferences(n, intervalNodeArray, intervalValueArray))  != SUCCESS
		|| (!intervalOnlyFlag && (errorFlag = divDifferences(n, nodeArray, normalValueArray)) != SUCCESS)) {
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
		intervalResult = newtonVal(intervalArithmetic, n, intervalNode, intervalNodeArray, intervalValueArray);
		string a,b;
		intervalArithmetic->IEndsToStrings(intervalResult, a, b);
		output->append("Using interval arithmetic:");
		output->append(QString("[") + QString(a.c_str()) + QString(" ; ") + QString(b.c_str()) + QString("]"));
		if (!intervalOnlyFlag) {
			long double node = (intervalNode.a + intervalNode.b)/2;
			normalResult = newtonVal(n, node, nodeArray, normalValueArray);
			output->append("Without interval arithmetic: ");
			output->append(translator->getNumberAsQString(normalResult));
		}
		delete [] nodeArray;
		delete [] intervalNodeArray;
		delete [] intervalValueArray;
		delete [] normalValueArray;
	}
	else {
		output->append("error");
	}
}

void Mathcore::newtonCoeffs(const QString & str) {
	bool intervalOnlyFlag = false;
	int n = translator->getNodeNumber(str, intervalOnlyFlag);
	if (n > 0) {
		QString polynomial, polynomialNormal;
		long double * nodeArray = new long double [n];		
		interval * intervalValueArray = new interval [n];
		interval * intervalNodeArray = new interval [n];
		long double * normalValueArray = new long double [n];
		bool isNegative = false;
		short errorFlag;
		interval xi;

		translator->stringToIntervals(intervalArithmetic, str, intervalNodeArray, intervalValueArray);
		for (int i = 0; i < n; ++i) {
			normalValueArray[i] = (intervalValueArray[i].a + intervalValueArray[i].b)/2;
			nodeArray[i] = (intervalNodeArray[i].a + intervalNodeArray[i].b)/2;
		}
		if ((errorFlag = divDifferences(n, intervalNodeArray, intervalValueArray))  != SUCCESS
		|| (!intervalOnlyFlag && (errorFlag = divDifferences(n, nodeArray, normalValueArray)) != SUCCESS)) {
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
		newtonCoeff(intervalArithmetic, n, intervalNodeArray, intervalValueArray);
		string a,b;
		if (!intervalOnlyFlag) {
			newtonCoeff(n, nodeArray, normalValueArray);
			for (int j = 0; j < n; ++j) {
				if (normalValueArray[j] != 0.0) {
					xi.a = xi.b = normalValueArray[j];
					intervalArithmetic->IEndsToStrings(xi, b, b);
					if (!polynomialNormal.isEmpty()) {
						if (b[0] == '-') {
							b.erase(0,1);
							isNegative = true;
						}
						polynomialNormal += isNegative ? " - " : " + ";
					}
					polynomialNormal += QString(b.c_str()) + translator->getExponentAsUnicode(n-j-1);
					isNegative = false;
				}
			}
			output->append("Without interval arithmetic:");
			output->append(polynomialNormal);
		}
		for (int j = 0; j < n; ++j) {
			if (intervalValueArray[j].a != 0.0 || intervalValueArray[j].b != 0.0) {
				intervalArithmetic->IEndsToStrings(intervalValueArray[j], a, b);
				if (!polynomial.isEmpty()) {
					polynomial += " + ";
				}
				
				polynomial += QString("[") + QString(a.c_str()) + QString(" ; ") + QString(b.c_str()) + QString("] ") + translator->getExponentAsUnicode(n-j-1);
			}
		}
		output->append("Using interval arithmetic:");
		output->append(polynomial);
		delete [] nodeArray;
		delete [] intervalNodeArray;
		delete [] intervalValueArray;
		delete [] normalValueArray;
	}
	else
		output->append("error");
}

void Mathcore::setOutput(QTextEdit * output) {
	this->output = output;
}

interval newtonVal(IntervalArithmetic * ia, uint n, interval node, interval * nodeArray, interval * valueArray) {
	
	interval buf, result = valueArray[0];
	for (uint i = 1; i < n; ++i) {
		buf =  ia->ISub(node, nodeArray[i]);
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

void newtonCoeff(IntervalArithmetic * ia, uint n, interval * nodeArray, interval * valueArray) {

	for (uint i = 1; i < n; ++i) {
		for (uint j = i; j > 1; --j) {
			valueArray[j] = ia->ISub(valueArray[j], ia->IMul(valueArray[j-1], nodeArray[i]));
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
