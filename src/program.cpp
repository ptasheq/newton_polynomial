#include "libs.h"
#include "gui.h"
#include <iostream>

Program::~Program() {
	delete gui;
}

void Program::run() {
	gui->run(app);
}

int Program::run(int argc, char * argv[]) {
	QApplication app(argc, argv);
	Program program(&app);
	program.run();
	return app.exec();
}
