#ifndef MATHCORE_H
#define MATHCORE_H

#include "interval_arithmetic.h"
#include <exception>
#include <QObject>
#include <QString>

typedef unsigned int uint;

class Mathcore: public QObject {
	Q_OBJECT
	private:
		long double * valueArray;
		uint arraySize; 
		Mathcore() : valueArray(NULL), arraySize(0) {}
	public:
		~Mathcore();
		long double newtonValue(uint, int *, long double *, int);
		void newtonCoeffs(uint, int *, long double *);
		void getValuesAsString(char *);
		static Mathcore & getInstance();
	public slots:
		void divDifferences(const QString &);
};

#endif

