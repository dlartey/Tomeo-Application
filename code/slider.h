#ifndef SLIDER_H
#define SLIDER_H
#include <QSlider>

class Slider : public QSlider {
    Q_OBJECT

public:

     Slider() :  QSlider() {
    }


public slots:
     //Home page.
    void slidingbar(int progress);
};

#endif // SLIDER_H
