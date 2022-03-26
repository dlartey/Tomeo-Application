#include "other_buttons.h"

void controlButtons::lightmode() {
    if(getlightmode()){
        setStyleSheet("QPushButton {border: 2px solid #8f8f91;"
                                      "border-image:url(:/icons/darkmode.png);"
                                      "border-radius: 6px;"
                                      "max-width: 50%;"
                                      "min-width: 50%;"
                                      "max-height: 50%;"
                                      "min-height: 50%;"
                                      "}");
        setlightmode(false);
    }
    else {
        setStyleSheet("QPushButton {border: 2px solid #8f8f91;"
                                      "border-image:url(:/icons/lightmode.png);"
                                      "border-radius: 6px;"
                                      "max-width: 50%;"
                                      "min-width: 50%;"
                                      "max-height: 50%;"
                                      "min-height: 50%;"
                                      "}");
        setlightmode(true);
    }

}

void controlButtons::isplaying() {
    if(getplaying()){
        setStyleSheet("QPushButton {border: 2px solid #8f8f91;"
                                      "border-image:url(:/icons/pause.png);"
                                      "border-radius: 6px;"
                                      "max-width: 50%;"
                                      "min-width: 50%;"
                                      "max-height: 50%;"
                                      "min-height: 50%;"
                                      "}");
        setplaying(false);
    }
    else {
        setStyleSheet("QPushButton {border: 2px solid #8f8f91;"
                                      "border-image:url(:/icons/play.png);"
                                      "border-radius: 6px;"
                                      "max-width: 50%;"
                                      "min-width: 50%;"
                                      "max-height: 50%;"
                                      "min-height: 50%;"
                                      "}");
        setplaying(true);
    }

}

void controlButtons::muted() {
    if(!getmuted()){
        setStyleSheet("QPushButton {border: 2px solid #8f8f91;"
                                      "border-image:url(:/icons/volume-mute.png);"
                                      "border-radius: 6px;"
                                      "max-width: 50%;"
                                      "min-width: 50%;"
                                      "max-height: 50%;"
                                      "min-height: 50%;"
                                      "}");
        setmuted(true);
    }
    else {
        setStyleSheet("QPushButton {border: 2px solid #8f8f91;"
                                      "border-image:url(:/icons/volume-up.png);"
                                      "border-radius: 6px;"
                                      "max-width: 50%;"
                                      "min-width: 50%;"
                                      "max-height: 50%;"
                                      "min-height: 50%;"
                                      "}");
        setmuted(false);
    }

}
