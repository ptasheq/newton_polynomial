#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QString>
#include <QChar>

class Translator {
	private:
		Translator(){}	
	public:
		~Translator();
		static Translator & getInstance();
		short getNodeNumber(const QString &);
};

#endif
