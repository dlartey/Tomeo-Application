#include "responsive_layout.h"
#include <QLabel>

void ResponsiveLayout::setGeometry(const QRect &r ) { // our layout should fit inside r
    QLayout::setGeometry(r);

    for (int i = 0; i < list_.size(); i++) {

        QLayoutItem *o = list_.at(i);

        try {
            QLabel *label = static_cast<QLabel *>(o->widget());
            if(label->objectName() == "Button")
            {
                label->setGeometry((r.width() + 5)/2, (r.y() + r.height() / 4),
                                   (r.width()-15)/2,r.height()/2);
            }
            else if(label->objectName() == "Title")
            {
                label->setGeometry(r.x()+r.width()/4, r.y() + 5, 100, 100);
            }
            else if(label->objectName() == "Instructions")
            {
                label->setGeometry(r.x()+30, r.y() + 110, 700, 400);
            }
            else if(label->objectName() == "loaded")
            {
                label->setGeometry((r.width() + 5)/2, r.y() + r.height() / 4 - 105, 700, 100);
            }

        }
        catch (std::bad_cast const&) {

        }
    }
}



// following methods provide a trivial list-based implementation of the QLayout class
int ResponsiveLayout::count() const {

    return list_.size();
}

QLayoutItem *ResponsiveLayout::itemAt(int idx) const {

    return list_.value(idx);
}

QLayoutItem *ResponsiveLayout::takeAt(int idx) {

    return idx >= 0 && idx < list_.size() ? list_.takeAt(idx) : 0;
}

void ResponsiveLayout::addItem(QLayoutItem *item) {

    list_.append(item);
}

QSize ResponsiveLayout::sizeHint() const {

    return minimumSize();
}

QSize ResponsiveLayout::minimumSize() const {

    return QSize(320,320);
}

ResponsiveLayout::~ResponsiveLayout() {

    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}
