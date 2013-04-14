#include "libs.h"

Program::~Program() {
}

void Program::createGui() {
	window = new QWidget();
	coeffBtn = new QPushButton(CAPTION, window);
	valueBtn = new QPushButton(CAPTION, window);

	coeffBtn->setGeometry(420, 40, BTN_WIDTH, BTN_HEIGHT);
	valueBtn->setGeometry(420, 200, BTN_WIDTH, BTN_HEIGHT);

	coeffLabel = new QLabel("Coefficients of the Newton polynomial", window);
	valueLabel = new QLabel("Value of the Newton polynomial", window);

	coeffLabel->setFont(QFont("Purisa", 11));
	valueLabel->setFont(QFont("Purisa", 11));

	coeffLabel->setGeometry(80, 10, 320, 30);
	valueLabel->setGeometry(110, 170, 280, 30);

	

	window->resize(WIDTH, HEIGHT);
	window->setWindowTitle(TITLE);
	window->setGeometry(QStyle::alignedRect(
		Qt::LeftToRight, Qt::AlignCenter, window->size(),
		app->desktop()->availableGeometry())
	);
	window->show(); 
}

void Program::destroyGui() {
	delete coeffLabel;
	delete valueLabel;
	delete coeffBtn;
	delete valueBtn;
	delete window;
}

void Program::run() {
	createGui();
}

int Program::run(int argc, char * argv[]) {
	QApplication app(argc, argv);
	Program program(&app);
	program.run();
	int status = app.exec();
	program.destroyGui();
	return status;
}
