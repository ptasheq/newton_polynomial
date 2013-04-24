#include "translator.h"

Translator::~Translator() {
}

// looks for improper characters

bool Translator::checkString(const QString & str) {
	int i;
	for (i = 0; i < str.size(); ++i) {
		if (!isProperCharacter(str[i]))
			break;
	}
	return (i == str.size());
}

bool Translator::isProperCharacter(const QChar & ch) {
	return ((ch <= '0' || ch >= '9') && ch != ' ' && ch != '.' && ch != '\n');
}

Translator & Translator::getInstance() {
	static Translator instance;
	return instance;
}


