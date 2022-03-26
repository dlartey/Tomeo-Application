#ifndef OTHER_BUTTONS_H
#define OTHER_BUTTONS_H

#include <QPushButton>

class controlButtons : public QPushButton
{
    Q_OBJECT

public:
    controlButtons() : QPushButton(){
        light_mode=true;
        playing = true;
        ismuted = false;
    }

    bool getlightmode() {
        return light_mode;
    }

    void setlightmode(bool val) {
        light_mode = val;
    }

    bool getplaying() {
        return playing;
    }

    void setplaying(bool val) {
        playing = val;
    }

    bool getmuted() {
        return ismuted;
    }

    void setmuted(bool val) {
        ismuted = val;
    }

private:
    bool light_mode;
    bool playing;
    bool ismuted;


private slots:
    void lightmode();
    void isplaying();
    void muted();

};

#endif // OTHER_BUTTONS_H
