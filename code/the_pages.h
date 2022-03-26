#ifndef THE_PAGES_H
#define THE_PAGES_H

#include <QStackedWidget>

class Pages : public QStackedWidget
{
    Q_OBJECT
public:
    Pages(QWidget *parent) :  QStackedWidget(parent) {
   }

public slots:
    void setIndex(int value);
};

#endif // THE_PAGES_H
