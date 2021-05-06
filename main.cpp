#include "BookTranslator.hpp"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BookTranslator w;
    w.show();
	
    return a.exec();
}
