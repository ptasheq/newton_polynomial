#ifndef LIBS_H
#define LIBS_H

#include <QApplication>
#include <QWidget>
#include <QStyle>
#include <QDesktopWidget>
#include <QPushButton>
#include <QLabel>
#include <QFile>
#include <QTextEdit>

#define HEIGHT 400
#define WIDTH 500
#define BTN_HEIGHT 30
#define BTN_WIDTH 75
#define TITLE "Newton Polynomial"
#define CAPTION "Calculate"
#define STYLE_FILE "style.qss"

class Program {
	private: 
		QApplication * app;
		QWidget * window;
		QPushButton * coeffBtn, * valueBtn;
		QLabel * coeffLabel, * valueLabel;
		QTextEdit * coeffEdit, * valueEdit;
		Program(QApplication * app) : app(app), window(NULL) {}
		void destroyGui();
		void createGui();
		void loadStyles();
	public:
		~Program();
		void run();
		static int run(int, char*[]);
};

#endif
