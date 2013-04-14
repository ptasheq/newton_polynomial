#ifndef LIBS_H
#define LIBS_H

#include <QApplication>
#include <QWidget>
#include <QStyle>
#include <QDesktopWidget>

#define HEIGHT 400
#define WIDTH 500
#define TITLE "Newton Polynomial"

class Program {
	private: 
		QApplication * app;
		QWidget * window;
		Program(QApplication * app) : app(app), window(NULL) {}
		void destroyGui();
		void createGui();
	public:
		~Program();
		void run();
		static int run(int, char*[]);
		const QApplication * getApp();
		const QWidget * getWindow();		
};

#endif
