#include "MainWindow.hpp"

#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QString>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>
//#include "QtXml/QtXml"
//#include <QStringList>

MainWindow::MainWindow(QMainWindow* parent):
	QMainWindow(parent)
{
	resize(600, 480);
	setWindowIcon(QIcon("images/book.png"));

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
	
	qApp->setAttribute(Qt::AA_DontShowIconsInMenus, false);

	connect(quit, &QAction::triggered, qApp, &QApplication::quit);
	connect(open, &QAction::triggered, this, &MainWindow::open_fb2);

	QPixmap book_title("images/book_title.png");
	m_title.setParent(this);
	m_title.setPixmap(book_title);
	setCentralWidget(&m_title);
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

			// hide(); ����� �������, ��� ������� ������� ������ � �������!!!
			// show(); ������� ��� �������� ���������������� ����!
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