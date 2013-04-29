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

void Translator::stringToIntervals(intervalarth::IntervalArithmetic * ia, const QString & str, int * nodeArray, interval * intervalArray) {
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
				nodeArray[currentNode++] = std::atoi(buf.c_str());
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
