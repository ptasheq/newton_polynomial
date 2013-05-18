#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QString>
#include <QChar>
#include <string>
#include "interval_arithmetic.h"

#define EXP0 0x2070
#define EXP1 0x00b9
#define EXP2 0x00b2
#define EXP3 0x00b3
#define EXP4 0x2074
#define EXP5 0x2075
#define EXP6 0x2076
#define EXP7 0x2077
#define EXP8 0x2078
#define EXP9 0x2079

#define isLegalCharacter(x) ((x == ' ') || (x == '-') || (x == '.') || (x == '\n'))

using std::string;
using intervalarth::interval;

class Translator {
	
	public:
		Translator(){}	
		~Translator();
		unsigned short getNodeNumber(const QString &);
		void stringToIntervals(intervalarth::IntervalArithmetic *, const QString &, long double *, interval *);
		QString getExponentAsUnicode(int);
		QString getNumberAsQString(long double);
};

#endif
