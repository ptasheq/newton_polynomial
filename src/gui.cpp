#include "gui.h" 
#include "mathcore.h"

Gui::Gui() : width(WIDTH), height(HEIGHT), title(TITLE) {
	window = new QWidget();
	valueBtn = new QPushButton(CAPTION, window);
	coeffBtn = new QPushButton(CAPTION, window);
	coeffLabel = new QLabel("Coefficients of the Newton polynomial", window);
	valueLabel = new QLabel("Value of the Newton polynomial", window);
	coeffEdit = new QTextEdit("", window);
	valueEdit = new QTextEdit("", window);

}

Gui::~Gui() {
	delete coeffBtn;
	delete valueBtn;
	delete coeffLabel;
	delete valueLabel;
	delete coeffEdit;
	delete valueEdit;
	delete window;
}

void Gui::loadStyles() {
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

void Gui::prepare() {
	coeffBtn->setGeometry(410, 35, BTN_WIDTH, BTN_HEIGHT);
	valueBtn->setGeometry(410, 195, BTN_WIDTH, BTN_HEIGHT);

	coeffLabel->setGeometry(54, 10, 320, 30);
	valueLabel->setGeometry(75, 170, 280, 30);

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

	// Associate buttons with events
	QObject::connect(coeffBtn, SIGNAL(clicked()), app, 
		SLOT(Mathcore::getInstance().divDifferences())
	);
}

void Gui::run(QApplication * app) {
	this->app = app;
	prepare();
	window->show();
}

