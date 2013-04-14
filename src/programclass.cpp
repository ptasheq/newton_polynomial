#include "libs.h"

Program::~Program() {
	destroyGui();
}

void Program::createGui() {
	window = new QWidget();
	window->resize(WIDTH, HEIGHT);
	window->setWindowTitle(TITLE);
	window->setGeometry(QStyle::alignedRect(
		Qt::LeftToRight, Qt::AlignCenter, window->size(),
		app->desktop()->availableGeometry())
	);
	window->show(); 
}

void Program::destroyGui() {
	if (window)
		delete window;
}

void Program::run() {
	createGui();
}

int Program::run(int argc, char * argv[]) {
	QApplication app(argc, argv);
	Program program(&app);
	program.run();
	return app.exec();
}
