#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QString>

class Translator {
	private:
		Translator(){}	
	public:
		~Translator();
		static Translator & getInstance();
		bool checkString(const QString &);
	    bool isProperCharacter(const QChar &);

};

#endif
