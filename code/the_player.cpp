//
// Created by twak on 11/11/2019.
//

#include "the_player.h"

// all buttons have been setup, store pointers here
void ThePlayer::setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i) {
    buttons = b;
    infos = i;
    jumpTo(buttons -> at(0) -> info);
}


void ThePlayer::playStateChanged (QMediaPlayer::State ms) {
    switch (ms) {
        case QMediaPlayer::State::StoppedState:
            play(); // starting playing again...
            break;
    default:
        break;
    }
}

void ThePlayer::jumpTo (TheButtonInfo* button) {
    setMedia( * button -> url);
    setVolume(50);
    play();
}
void ThePlayer::pausing () {
pause();
}
void ThePlayer::playing () {
    if(getisplaying()) {
        pause();
        setisplaying(false);
    }
    else {
        play();
        setisplaying(true);
    }
}

void ThePlayer::mute()
{
    if(!getmuted())
    {
        setvol(volume());
        setVolume(0);
        setmuted(true);
        setMuted(true);
    }
    else {
        setVolume(vol);
        setmuted(false);
        setMuted(false);
    }
}


