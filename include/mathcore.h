#ifndef MATHCORE_H
#define MATHCORE_H

#include "interval_arithmetic.h"
#include "translator.h"
#include <exception>
#include <QObject>
#include <QString>
#include <QTextEdit>

typedef unsigned int uint;
using intervalarth::interval;

class Mathcore {
	private:
		interval * valueArray;
		uint * nodeArray; 
		QTextEdit * output;
		intervalarth::IntervalArithmetic * intervalArithmetic;
		Translator * translator;
		Mathcore();
	public:
		~Mathcore();
		void divDifferences(uint, uint *, long double *);
		void newtonValue(const QString &);
		void newtonCoeffs(const QString &);
		void getValuesAsString(char *);
		void setOutput(QTextEdit *);
		static Mathcore & getInstance();
};

#endif

