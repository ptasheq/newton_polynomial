#ifndef MATHCORE_H
#define MATHCORE_H

#include "interval_arithmetic.h"
#include "translator.h"
#include <exception>
#include <iostream>
#include <QObject>
#include <QString>
#include <QTextEdit>

#define isZero(str, n) ((n == 1 && str[0] == '0') || (n == 2 && str[0] == '-' && str[1] == '0'))

enum {SUCCESS, TOO_FEW_NODES, DIV_BY_ZERO, IDENTICAL_NODES};

typedef unsigned int uint;
using intervalarth::interval;
using intervalarth::IntervalArithmetic;

class Mathcore {
	private:
		QTextEdit * output;
		IntervalArithmetic * intervalArithmetic;
		Translator * translator;
		Mathcore();
	public:
		~Mathcore();
		short divDifferences(uint, interval *, interval *);
		short divDifferences(uint, long double *, long double *);
		void newtonValue(const QString &);
		void newtonCoeffs(const QString &);
		void getValuesAsString(char *);
		void setOutput(QTextEdit *);
		static Mathcore & getInstance();
};

interval newtonVal(IntervalArithmetic *, uint, interval, interval *, interval *);
long double newtonVal(uint, long double, long double *, long double *);
void newtonCoeff(IntervalArithmetic *, uint, interval *, interval *);
void newtonCoeff(uint, long double *, long double *);

#endif
