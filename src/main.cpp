#include "libs.h"

void createGui() {
	QWidget * window = new QWidget();
	window->resize(100, 100);
	window->setWindowTitle("cos");
	window->show();
}

int main(int argc, char *argv[]) {
	return Program::run(argc, argv);
}

