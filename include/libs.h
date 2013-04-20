#ifndef LIBS_H
#define LIBS_H

#include <QApplication>
#include "gui.h"

class Program {
	private: 
		QApplication * app;
		Gui * gui;
		Program(QApplication * app) : app(app), gui(new Gui()){}
	public:
		~Program();
		void run();
		static int run(int, char*[]);
};

#endif
