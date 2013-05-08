#ifndef MATHCORE_H
#define MATHCORE_H

#include "interval_arithmetic.h"
#include "translator.h"
#include <exception>
#include <iostream>
#include <QObject>
#include <QString>
#include <QTextEdit>
#include <QInputDialog>

#define isZero(str, n) ((n == 1 && str[0] == '0') || (n == 2 && str[0] == '-' && str[1] == '0'))

typedef unsigned int uint;
using intervalarth::interval;

class Mathcore {
	private:
		interval * intervalValueArray;
		long double * normalValueArray;
		int * nodeArray; 
		QTextEdit * output;
		intervalarth::IntervalArithmetic * intervalArithmetic;
		Translator * translator;
		Mathcore();
	public:
		~Mathcore();
		void divDifferences(uint, int *, interval *);
		void divDifferences(uint, int *, long double *);
		void newtonValue(const QString &);
		void newtonCoeffs(const QString &);
		void getValuesAsString(char *);
		void setOutput(QTextEdit *);
		static Mathcore & getInstance();
};

#endif

