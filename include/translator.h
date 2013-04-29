#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QString>
#include <QChar>
#include <string>
#include "interval_arithmetic.h"

#define isLegalCharacter(x) ((x == ' ') || (x == '-') || (x == '.') || (x == '\n'))

using std::string;
using intervalarth::interval;

class Translator {
	
	public:
		Translator(){}	
		~Translator();
		unsigned short getNodeNumber(const QString &);
		void stringToIntervals(intervalarth::IntervalArithmetic *, const QString &, int *, interval *);
};

#endif
