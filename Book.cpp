#include "Book.hpp"

#include <QtCore>
#include <QtXml/qxml.h>

Book::Book(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}