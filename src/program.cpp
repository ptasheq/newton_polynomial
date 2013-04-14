#include "libs.h"

Program::~Program() {
}

void Program::createGui() {
	window = new QWidget();
	coeffBtn = new QPushButton(CAPTION, window);
	valueBtn = new QPushButton(CAPTION, window);

	coeffBtn->setGeometry(410, 35, BTN_WIDTH, BTN_HEIGHT);
	valueBtn->setGeometry(410, 195, BTN_WIDTH, BTN_HEIGHT);

	coeffLabel = new QLabel("Coefficients of the Newton polynomial", window);
	valueLabel = new QLabel("Value of the Newton polynomial", window);

	coeffLabel->setGeometry(54, 10, 320, 30);
	valueLabel->setGeometry(75, 170, 280, 30);

	coeffEdit = new QTextEdit("", window);
	valueEdit = new QTextEdit("", window);

	coeffEdit->setGeometry(20, 35, 340, 100);
	valueEdit->setGeometry(20, 195, 340, 100);
	coeffEdit->setToolTip("Firstly, enter values of nodes seperated with space, then press enter and type function values");
	valueEdit->setToolTip("Firstly, enter values of nodes seperated with space, then press enter and type function values");

	window->resize(WIDTH, HEIGHT);
	window->setWindowTitle(TITLE);
	window->setGeometry(QStyle::alignedRect(
		Qt::LeftToRight, Qt::AlignCenter, window->size(),
		app->desktop()->availableGeometry())
	);
	loadStyles();
	window->show(); 
}

void Program::destroyGui() {
	delete coeffLabel;
	delete valueLabel;
	delete coeffBtn;
	delete valueBtn;
	delete window;
}

void Program::loadStyles() {
	QFile styleFile(STYLE_FILE);
	if (!styleFile.open(QFile::ReadOnly | QFile::Text)) {
		return;
	}
	QString style(styleFile.readAll());
	if (style.size() == 0) {
		return;
	}

	app->setStyleSheet(style);
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
