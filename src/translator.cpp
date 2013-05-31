#include "translator.h"
#include <sstream>
#include <iomanip>

Translator::~Translator() {
}

// checks if numbers of nodes and values are identical and returns the number

unsigned short Translator::getNodeNumber(const QString & str, bool & intervalFlag) {
	int i, nodes = 1, values = 1;
	bool afterEnter = false, inBrace = (str[0] == '[');
	if (str[0].isDigit() || str[0] == '-' || str[0] == '[') {
		for (i = 1; i < str.size(); ++i) {
			if (!str[i].isDigit()) {
				if ((!str[i-1].isDigit() && str[i-1] != ' ' && str[i] != '-'  && str[i] != '[' && str[i-1] != ']') || (inBrace && str[i] == '[') || 
					(!inBrace && (str[i] == ']' || str[i] == ';')) || !isLegalCharacter(str[i])) {
					break;
				}
				if (!inBrace && str[i] == ' ' && i < str.size()-1) { // we don't want count some odd spaces in the end
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
				else if (str[i] == '[') {
					inBrace = true;
				}
				else if (str[i] == ']') {
					intervalFlag = true;
					inBrace = false;
				}
			}
		}
		return ((i == str.size()) && (values == nodes)) ? nodes : 0;
	}
	return 0;
}

void Translator::stringToIntervals(intervalarth::IntervalArithmetic * ia, const QString & str, interval * nodeArray, interval * intervalArray) {

	std::string buf; 
	int currentNode = 0;
	bool afterEnter = false;

	for (int i = 0; i <= str.size(); ++i) {
		if ((str[i] == ' ' || str[i] == '\n' || i == str.size())) {
			if (!buf.empty()) {
				if (afterEnter) {
					intervalArray[currentNode++] = ia->IntRead(buf);
				}
				else {
					nodeArray[currentNode++] = ia->IntRead(buf);
				}
				buf.clear();
			}
			if (str[i] == '\n') {
				afterEnter = true;
				currentNode = 0;
			}
		}
		else if (str[i] == ';' ) { // in brace
			if (afterEnter) {
				intervalArray[currentNode].a = ia->LeftRead(buf);	
			}
			else {
				nodeArray[currentNode].a = ia->LeftRead(buf);
			}
			buf.clear();
		}
		else if (str[i] == ']') {
			if (afterEnter) {
				intervalArray[currentNode++].b = ia->RightRead(buf);
			}
			else {
				nodeArray[currentNode++].b = ia->RightRead(buf);
			}
			buf.clear();
		}
		else if (str[i] != '[') {
			buf += str[i].toAscii();
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
	std::stringstream ss;
	ss << std::scientific << std::setprecision(15) << x;
	return QString(ss.str().c_str());
}

interval Translator::getNodeFromDialog(intervalarth::IntervalArithmetic * ia, bool & intervalOnlyFlag) {
	QString str = QInputDialog::getText(0, QString("Enter desire node"), QString("Node:"));	
	int i = 0;
	std::string buf;
	interval tmp;

	if (str[0] == '[' && str.size() > 4) {
		intervalOnlyFlag = true;
		for (i = 1; i < str.size(); ++i) {
			if (str[i].isDigit() || str[i] == '.') {
				buf += str[i].toAscii();	
			}
			else if (str[i] == ';' && str[i-1].isDigit()) {
				tmp.a = ia->LeftRead(buf);	
				buf.clear();
			}
			else if (str[i] == ']' && i == str.size()-1 && str[i-1].isDigit()) {
				tmp.b = ia->RightRead(buf);
			}
			else {
				break;
			}
		}
	}
	else if (str[0].isDigit()) {
		buf += str[0].toAscii();
		for (i = 1; i < str.size(); ++i) {
			if (str[i].isDigit() || str[i] == '.') {
				buf += str[i].toAscii();
			}
			else {
				break;
			}
		}
		tmp = ia->IntRead(buf);
	}
	if (i < str.size()) {
		tmp.a = tmp.b = 0;
	}
	return tmp;
}
