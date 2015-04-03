#ifndef QT1_H
#define QT1_H

#include <QtWidgets/QMainWindow>
#include "ui_qt1.h"

class qt1 : public QMainWindow
{
	Q_OBJECT

public:
	qt1(QWidget *parent = 0);
	~qt1();

private:
	Ui::qt1Class ui;
};

#endif // QT1_H
