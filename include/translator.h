#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QString>
#include <QChar>
#include <string>
#include "interval_arithmetic.h"

using std::string;
using intervalarth::interval;

class Translator {
	
	public:
		Translator(){}	
		~Translator();
		short getNodeNumber(const QString &);
		void stringToIntervals(intervalarth::IntervalArithmetic *, const QString &, uint *, interval *);
};

#endif
