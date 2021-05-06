#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BookTranslator.h"

class BookTranslator : public QMainWindow
{
    Q_OBJECT

public:
    BookTranslator(QWidget *parent = Q_NULLPTR);

private:
    Ui::BookTranslatorClass ui;
};
