#include "Book.hpp"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Book book;
    book.show();
	
    return a.exec();
}
