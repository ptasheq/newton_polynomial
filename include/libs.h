#ifndef LIBS_H
#define LIBS_H

#include <QApplication>
#include <QWidget>
#include <QStyle>
#include <QDesktopWidget>
#include <QPushButton>
#include <QLabel>

#define HEIGHT 400
#define WIDTH 500
#define BTN_HEIGHT 30
#define BTN_WIDTH 75
#define TITLE "Newton Polynomial"
#define CAPTION "Calculate"

class Program {
	private: 
		QApplication * app;
		QWidget * window;
		QPushButton * coeffBtn, * valueBtn;
		QLabel * coeffLabel, * valueLabel;
		Program(QApplication * app) : app(app), window(NULL) {}
		void destroyGui();
		void createGui();
	public:
		~Program();
		void run();
		static int run(int, char*[]);
};

#endif
