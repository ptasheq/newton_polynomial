#include "gui.h" 

Gui::Gui() : width(WIDTH), height(HEIGHT), title(TITLE) {
	window = new QWidget();
	valueBtn = new QPushButton();
	coeffBtn = new QPushButton();
}

Gui::~Gui() {
	delete window;
	delete valueBtn;
	delete coeffBtn;
}

Gui & Gui::getInstance() {
	static Gui instance;
	return instance;
}

void Gui::prepare() {
	window->resize(width, height);
	window->setWindowTitle(title);
	window->setGeometry(QStyle::alignedRect(
		Qt::LeftToRight, Qt::AlignCenter, window->size(),
		app->desktop()->availableGeometry())
	);
}

void Gui::start(QApplication * app) {
	this->app = app;
	prepare();
	window->show();
}
