#include "stacked_widget.h"

void StackedWidget::changeIndex1(){
    setCurrentIndex(0);
    setStyleSheet("background-color: #2FDD92;");
}

void StackedWidget::changeIndex2(){
    setCurrentIndex(1);
    setStyleSheet("background-color: #69DADB;");
}

void StackedWidget::light_mode(){
    if(getlightmode()) {
        setStyleSheet("background-color: rgb(160,160,160);");
        setlightmode(false);
    }
    else {
        setStyleSheet("background-color:rgb(238,238,238);");
        setlightmode(true);

    }
}
