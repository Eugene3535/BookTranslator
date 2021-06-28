#include "MainWindow.hpp"

#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QString>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>

#include "QtXml/QtXml"
#include <QStringlist>

MainWindow::MainWindow(QMainWindow* parent):
	QMainWindow(parent)
{
	// Title settings
	resize(1200, 720);
	setWindowIcon(QIcon("images/book.png"));
	setCentralWidget(&m_browser);

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
			//write_log("Sucsess!");

			// hide(); Важно помнить, что процесс остаётся висеть в реестре!!!
			// show(); Вызвать при закрытии вспомогательного окна!

			QXmlStreamReader sr(&file);
			QString book;
			QString imgId;
			QString imgType;
			QStringList thisToken;

			while (!sr.atEnd())
			{
				switch (sr.readNext())
				{
				case QXmlStreamReader::NoToken:
					qDebug() << "QXmlStreamReader::NoToken";
					break;
				case QXmlStreamReader::StartDocument:
					book = "<!DOCTYPE HTML><html><body style=\"font-size:14px\">";
					break;
				case QXmlStreamReader::EndDocument:
					book.append("</body></html>");
					break;
				case QXmlStreamReader::StartElement:
					thisToken.append(sr.name().toString());
					if (sr.name().toString() == "image") // расположение рисунков
					{
						if (sr.attributes().count() > 0)
							book.append("<p align=\"center\">" + sr.attributes().at(0).value().toString() + "</p>");
					}
					if (sr.name() == "binary") // хранилище рисунков
					{
						imgId = sr.attributes().at(0).value().toString();
						imgType = sr.attributes().at(1).value().toString();
					}
					break;
				case QXmlStreamReader::EndElement:
					if (thisToken.last() == sr.name().toString())
						thisToken.removeLast();
					else
						qDebug() << "error token";
					break;
				case QXmlStreamReader::Characters:
					if (sr.text().toString().contains(QRegExp("[A-Z]|[a-z]|[А-Я]|[а-я]"))) // если есть текст в блоке
					{
						if (thisToken.contains("description")) // ОПИСАНИЕ КНИГИ
						{
							break; // не выводим
						}
						if (thisToken.contains("div"))
							break;
						if (!thisToken.contains("binary"))
							book.append("<p>" + sr.text().toString() + "</p>");
					}
					if (thisToken.contains("binary"))//для рисунков
					{
						QString image = "<img src=\"data:"
							+ imgType + ";base64,"
							+ sr.text().toString()
							+ "\"/>";
						book.replace("#" + imgId, image);
					}
					break;
				}
			}
			file.close();
			m_browser.setHtml(book);
			m_browser.setVerticalScrollBar(0);
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