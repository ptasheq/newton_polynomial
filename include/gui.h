#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QPushButton>
#include <QStyle>
#include <QDesktopWidget>
#include <QApplication>

#define HEIGHT 400
#define WIDTH 500
#define TITLE "Newton Polynomial"
#define BTN_CAPTION "Calculate"

class Gui {
	private:
		QApplication * app;
		QWidget * window;
		QPushButton * valueBtn;
		QPushButton * coeffBtn;
		int width, height;
		QString title;
		void prepare();
		Gui();
	public:
		~Gui();
		static Gui & getInstance();
		void start(QApplication *);
};

#endif
