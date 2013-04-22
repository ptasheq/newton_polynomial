#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QPushButton>
#include <QStyle>
#include <QDesktopWidget>
#include <QApplication>
#include <QLabel>
#include <QFile>
#include <QTextEdit>
#include <QSignalMapper>
#include <QString>

#define HEIGHT 500
#define WIDTH 500
#define BTN_HEIGHT 30
#define BTN_WIDTH 75
#define TITLE "Newton Polynomial"
#define CAPTION "Calculate"
#define STYLE_FILE "style.qss"

class Gui {
	private:
		QApplication * app;
		QWidget * window;
		QSignalMapper * signalMapper;
		QPushButton * valueBtn, * coeffBtn;
		QLabel * coeffLabel, * valueLabel, * resultLabel;
		QTextEdit * coeffEdit, * valueEdit, * resultEdit;
		int width, height;
		QString title;
		void loadStyles();
		void prepare();
	public:
		Gui();
		~Gui();
		void run(QApplication *);
};

#endif
