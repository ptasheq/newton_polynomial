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

typedef unsigned int uint;
using intervalarth::interval;

class Mathcore {
	private:
		interval * valueArray;
		int * nodeArray; 
		QTextEdit * output;
		intervalarth::IntervalArithmetic * intervalArithmetic;
		Translator * translator;
		Mathcore();
	public:
		~Mathcore();
		void divDifferences(uint, int *, interval *);
		void newtonValue(const QString &);
		void newtonCoeffs(const QString &);
		void getValuesAsString(char *);
		void setOutput(QTextEdit *);
		static Mathcore & getInstance();
};

#endif

