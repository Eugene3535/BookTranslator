#include "MainWindow.hpp"

#include <QMenu>
#include <QMenuBar>

#include <QTextStream>
#include <QFile>
#include <QFileDialog>

MainWindow::MainWindow(QMainWindow* parent)
	: QMainWindow(parent)
{
	resize(800, 600);

	// File menu
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

	// Language menu
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
	connect(open, &QAction::triggered, this, &MainWindow::open_fb2);
}

void MainWindow::open_fb2()
{
	QString file_path = QFileDialog::getOpenFileName(this, "open", QDir::currentPath(), "");

	if (file_path.isEmpty())
		return;

	if (file_path.endsWith(".fb2"))
	{
		QFile file(file_path);

		if (file.open(QIODevice::ReadWrite | QIODevice::Text))
		{
			write_log("Sucsess!");
		}
	}

}

void MainWindow::write_log(const QString& info)
{
	QTextStream out(stdout);
	QString filename = "D://Projects/Qt/BookTranslator/BookTranslator/loginfo/log.txt";
	QFile file(filename);

	if (file.open(QIODevice::WriteOnly)) 
	{
		QTextStream out(&file); 
		out << info << endl;		
	}
	else 
		qWarning("Could not open file");
	
	file.close();
}