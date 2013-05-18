#include "translator.h"

Translator::~Translator() {
}

// checks if numbers of nodes and values are identical and returns the number

unsigned short Translator::getNodeNumber(const QString & str) {
	int i, nodes = 1, values = 1;
	bool afterEnter = false;
	if (str[0].isDigit() || str[0] == '-') {
		for (i = 1; i < str.size(); ++i) {
			if (!str[i].isDigit()) {
				if ((!str[i-1].isDigit() && str[i-1] != ' ' && str[i] != '-') || 
				!isLegalCharacter(str[i])) {
					break;
				}
				if (str[i] == ' ' && i < str.size()-1) { // we don't want count some odd spaces in the end
					if (afterEnter) {
						++values;
					}
					else {
						++nodes;
					}
				}
				else if (str[i] == '\n' && i < str.size()-1) {
					if (afterEnter) { // there should be only one enter
						break;
					}
					afterEnter = true;
				}
			}
		}
		return ((i == str.size()) && (values == nodes)) ? nodes : 0;
	}
	return 0;
}

void Translator::stringToIntervals(intervalarth::IntervalArithmetic * ia, const QString & str, long double * nodeArray, interval * intervalArray) {
	std::string buf;
	int numberLength = 0, currentNode = 0;
	bool afterEnter = false;

	for (int i = 0; i < str.size(); ++i) {
		buf[numberLength] = str[i].toAscii();
		if (str[i] == ' ' || str[i] == '\n' || i == str.size()-1) {
			numberLength = 0;
			if (afterEnter) {
				intervalArray[currentNode++] = ia->IntRead(buf);
			}
			else {
				nodeArray[currentNode++] = ia->LeftRead(buf);
			}
			if (str[i] == '\n') {
				afterEnter = true;
				currentNode = 0;
			}
			buf.clear();
		}
		else {
			++numberLength;	
		}
	}
}

QString Translator::getExponentAsUnicode(int exp) {
	QString str = (exp > 0) ? "x" : "";
	while (exp > 0) {
		switch(exp % 10) {
			case 1:
				str += QChar(EXP1);
				break;
			case 2: 
				str += QChar(EXP2);
				break;
			case 3: 
				str += QChar(EXP3);
				break;
			case 4:
				str += QChar(EXP4);
				break;
			case 5: 
				str += QChar(EXP5);
				break;
			case 6: 
				str += QChar(EXP6);
				break;
			case 7:
				str += QChar(EXP7);
				break;
			case 8: 
				str += QChar(EXP8);
				break;
			case 9: 
				str += QChar(EXP9);
				break;
			default:
				str += QChar(EXP0);
		}
		exp /= 10;
	}
	return str;
}

QString Translator::getNumberAsQString(long double x) {
	return QString(boost::lexical_cast<std::string>(x).c_str());
}
