#include "MainWindow.hpp"

#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow(QMainWindow* parent)
	: QMainWindow(parent)
{
	resize(800, 600);

	QPixmap openpix("images/open.png");
	QPixmap savepix("images/save.png");
	QPixmap quitpix("images/close.png");

	QAction* open = new QAction(openpix, "&Open", this);
	QAction* save = new QAction(savepix, "&Save", this);
	QAction* quit = new QAction(quitpix, "&Quit", this);

	// TODO: mb, need to add a shortcuts ?
	//quit->setShortcut(tr("CTRL+Q"));

	QMenu* file;
	file = menuBar()->addMenu("&File");
	file->addAction(open); 
	file->addSeparator();
	file->addAction(save);
	file->addSeparator();
	file->addAction(quit); 
	
	qApp->setAttribute(Qt::AA_DontShowIconsInMenus, false);

	connect(quit, &QAction::triggered, qApp, &QApplication::quit);
}