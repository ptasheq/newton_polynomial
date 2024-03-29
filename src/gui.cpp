#include "gui.h" 
#include "mathcore.h"
#include "translator.h"

Gui::Gui() : width(WIDTH), height(HEIGHT), title(TITLE) {
	window = new QWidget();
	valueBtn = new QPushButton(CAPTION, window);
	coeffBtn = new QPushButton(CAPTION, window);
	coeffLabel = new QLabel("Data for coefficients of the Newton polynomial", window);
	valueLabel = new QLabel("Data for value of the Newton polynomial", window);
	resultLabel = new QLabel("Calculations results", window);
	coeffEdit = new QTextEdit("", window);
	valueEdit = new QTextEdit("", window);
	resultEdit = new QTextEdit("", window);
}

Gui::~Gui() {
	delete coeffBtn;
	delete valueBtn;
	delete coeffLabel;
	delete valueLabel;
	delete resultLabel;
	delete coeffEdit;
	delete valueEdit;
	delete resultEdit;
	delete signalMapper;
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

	coeffLabel->setGeometry(44, 10, 320, 30);
	valueLabel->setGeometry(55, 170, 280, 30);
	resultLabel->setGeometry(175, 330, 200, 30);

	coeffEdit->setGeometry(20, 35, 340, 100);
	valueEdit->setGeometry(20, 195, 340, 100);
	resultEdit->setGeometry(20, 355, 460, 125);
	coeffEdit->setToolTip("Firstly, enter values of nodes seperated with space, then press enter and type function values");
	valueEdit->setToolTip("Firstly, enter values of nodes seperated with space, then press enter and type function values");
	resultEdit->setToolTip("Here results of your calculaions are displayed");

	resultEdit->setReadOnly(true);

	window->resize(WIDTH, HEIGHT);
	window->setWindowTitle(TITLE);
	window->setGeometry(QStyle::alignedRect(
		Qt::LeftToRight, Qt::AlignCenter, window->size(),
		app->desktop()->availableGeometry())
	);
	loadStyles();

	Mathcore::getInstance().setOutput(resultEdit);

	// Associate buttons with events
	signalMapper = new QSignalMapper(this);
	signalMapper->setMapping(coeffBtn, COEFF_BTN);
	signalMapper->setMapping(valueBtn, VALUE_BTN);
	QObject::connect(coeffBtn, SIGNAL(clicked()), 
		signalMapper, SLOT(map()));
	QObject::connect(valueBtn, SIGNAL(clicked()),
		signalMapper, SLOT(map()));
	QObject::connect(signalMapper, SIGNAL(mapped(const int)),
		this, SLOT(onButtonClick(const int)));
}

void Gui::onButtonClick(const int objectId) {
	switch(objectId) {
		case COEFF_BTN:
			Mathcore::getInstance().newtonCoeffs(coeffEdit->toPlainText());
			break;
		case VALUE_BTN:
			Mathcore::getInstance().newtonValue(valueEdit->toPlainText());
			break;
		default:
		break;
	}
}

void Gui::run(QApplication * app) {
	this->app = app;
	prepare();
	window->show();
}

