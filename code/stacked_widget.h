#ifndef STACKED_WIDGET_H
#define STACKED_WIDGET_H

#include <QStackedWidget>

class StackedWidget : public QStackedWidget {
    Q_OBJECT

private:
    bool lightmode;
    bool isplaying;

public:

     StackedWidget() :  QStackedWidget() {
         lightmode = true;
    }
     bool getlightmode() {
         return lightmode;
     }
     void setlightmode(bool val) {
         lightmode = val;
     }

private slots:
     //Home page.
     void changeIndex1();

     //Pages for the different video tags.
     void changeIndex2();
     void light_mode();
};

#endif

