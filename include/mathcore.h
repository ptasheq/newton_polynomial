#ifndef MATHCORE_H
#define MATHCORE_H

#include "interval_arithmetic.h"
#include <exception>
#include <QObject>
#include <QString>
#include <QTextEdit>

typedef unsigned int uint;

class Mathcore {
	private:
		long double * valueArray;
		uint arraySize; 
		QTextEdit * output;
		intervalarth::IntervalArithmetic * intervalArithmetic;
		Mathcore() : valueArray(NULL), arraySize(0), output(NULL), 
			intervalArithmetic(new intervalarth::IntervalArithmetic()) {}
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

