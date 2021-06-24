#include "MainWindow.hpp"

#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow(QMainWindow* parent)
	: QMainWindow(parent)
{
	resize(800, 600);

	QPixmap open_icon("images/open.png");
	QPixmap save_icon("images/save.png");
	QPixmap quit_icon("images/quit.png");

	QAction* open = new QAction(open_icon, "&Open", this);
	QAction* save = new QAction(save_icon, "&Save", this);
	QAction* quit = new QAction(quit_icon, "&Quit", this);

	QMenu* file_menu;
	file_menu = menuBar()->addMenu("&File");
	file_menu->addAction(open);
	file_menu->addSeparator();
	file_menu->addAction(save);
	file_menu->addSeparator();
	file_menu->addAction(quit);

	QPixmap russian_icon("images/russia.png");
	QPixmap usa_icon("images/usa.png");
	
	QAction* russian = new QAction(russian_icon, "&Russian", this);
	QAction* usa = new QAction(usa_icon, "&USA", this);

	QMenu* language_menu;
	language_menu = menuBar()->addMenu("&Language");
	language_menu->addAction(russian);
	language_menu->addSeparator();
	language_menu->addAction(usa);
	
	// TODO: mb, need to add a shortcuts ?
	//quit->setShortcut(tr("CTRL+Q"));	
	
	qApp->setAttribute(Qt::AA_DontShowIconsInMenus, false);

	connect(quit, &QAction::triggered, qApp, &QApplication::quit);
}