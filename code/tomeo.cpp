
#include <iostream>
#include <QApplication>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlaylist>
#include <string>
#include <vector>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QFileInfo>
#include <QtWidgets/QFileIconProvider>
#include <QDesktopServices>
#include <QImageReader>
#include <QMessageBox>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include "the_player.h"
#include "the_button.h"
#include "QStackedWidget"
#include "QProgressBar"
#include "QSlider"
#include <QLayout>
#include <QLabel>
#include <QScrollArea>
#include "responsive_layout.h"
#include "stacked_widget.h"
#include "other_buttons.h"

// read in videos and thumbnails to this directory
std::vector<TheButtonInfo> getInfoIn (std::string loc) {

    std::vector<TheButtonInfo> out =  std::vector<TheButtonInfo>();
    QDir dir(QString::fromStdString(loc) );
    QDirIterator it(dir);
    while (it.hasNext()) { // for all files

        QString f = it.next();

            if (f.contains("."))

#if defined(_WIN32)
            if (f.contains(".wmv"))  { // windows
#else
            if (f.contains(".mp4") || f.contains("MOV"))  { // mac/linux
#endif

            QString thumb = f.left( f .length() - 4) +".png";
            if (QFile(thumb).exists()) { // if a png thumbnail exists
                QImageReader *imageReader = new QImageReader(thumb);
                    QImage sprite = imageReader->read(); // read the thumbnail
                    if (!sprite.isNull()) {
                        QIcon* ico = new QIcon(QPixmap::fromImage(sprite)); // voodoo to create an icon for the button
                        QUrl* url = new QUrl(QUrl::fromLocalFile( f )); // convert the file location to a generic url
                        out . push_back(TheButtonInfo( url , ico  ) ); // add to the output list
                    }
                    else
                        qDebug() << "warning: skipping video because I couldn't process thumbnail " << thumb << endl;
            }
            else
                qDebug() << "warning: skipping video because I couldn't find thumbnail " << thumb << endl;
        }
    }

    return out;
}

int main(int argc, char *argv[]) {

    // let's just check that Qt is operational first
    qDebug() << "Qt version: " << QT_VERSION_STR << endl;
    // create the Qt Application
    QApplication app(argc, argv);
    // collect all the videos in the folder
    std::vector<TheButtonInfo> videos;
    if (argc == 2)
        videos = getInfoIn( std::string(argv[1]) );

    if (videos.size() == 0) {

        const int result = QMessageBox::question(
                    NULL,
                    QString("Tomeo"),
                    QString("no videos found! download, unzip, and add command line argument to \"quoted\" file location. Download videos from Tom's OneDrive?"),
                    QMessageBox::Yes |
                    QMessageBox::No );

        switch( result )
        {
        case QMessageBox::Yes:
          QDesktopServices::openUrl(QUrl("https://leeds365-my.sharepoint.com/:u:/g/personal/scstke_leeds_ac_uk/EcGntcL-K3JOiaZF4T_uaA4BHn6USbq2E55kF_BTfdpPag?e=n1qfuN"));
          break;
        default:
            break;
        }
        exit(-1);
    }

    StackedWidget * stackedWidget = new StackedWidget();
    stackedWidget->setStyleSheet("background-color: #2FDD92;");


    // the QMediaPlayer which controls the playback
    QVideoWidget *videoWidget = new QVideoWidget;
    ThePlayer *player = new ThePlayer;
    player->setVideoOutput(videoWidget);

    // a row of buttons
    QWidget *buttonWidget = new QWidget();

    //Tags
    QLabel *descriptortags = new QLabel();
    descriptortags->setText("Tags: Mountains, POV");
    descriptortags->setStyleSheet("font-size: 14pt");
    // a list of the buttons
    std::vector<TheButton*> buttons;
    // the buttons are arranged vertically
    QVBoxLayout *layout = new QVBoxLayout();
    buttonWidget->setLayout(layout);

    for ( int i = 0; i < videos.size(); i++ ) {
        //create the video buttons.
        TheButton *button = new TheButton(buttonWidget);
        button->connect(button, SIGNAL(jumpTo(TheButtonInfo*)), player, SLOT (jumpTo(TheButtonInfo*))); // when clicked, tell the player to play.
        buttons.push_back(button);
        layout->addWidget(button);
        button->init(&videos.at(i));
    }

    //custom layout for homepage
    ResponsiveLayout * rl = new ResponsiveLayout();
    QLabel *title = new QLabel();
    title->setObjectName("Title");
    title->setTextFormat(Qt::RichText);
    title->setText("Tomeo");
    title->setStyleSheet("font-weight:bold; font-size: 18pt");

    QLabel *instr = new QLabel();
    instr->setTextFormat(Qt::RichText);
    instr->setObjectName("Instructions");
    instr->setStyleSheet("font-size: 12pt");
    instr->setWordWrap(true);
    instr->setText("Welcome to Tomeo!<br><br>"
                   "To use this application and view videos press the button on the right.<br>"
                   "This will take you to the video player where you can choose which videos<br>"
                   "to watch.<br><br>"
                   "The video thumbnails will appear on the left which can be used to play the<br>"
                   "desired video. The video can be paused at anytime and the a dark or light <br>"
                   "theme can be chosen using the sun icon.");

    QLabel *loaded = new QLabel();
    loaded->setObjectName("loaded");
    loaded->setTextFormat(Qt::RichText);
    loaded->setStyleSheet("font: italic; font-size: 12pt");
    QString s = QString::number(videos.size());
    loaded->setText("No. of videos loaded: " + s);
    rl->addWidget(title);
    rl->addWidget(instr);
    rl->addWidget(loaded);


    //Page buttons
    QPushButton *home_button_1 = new QPushButton();
    home_button_1->setStyleSheet("QPushButton {border: 2px solid #8f8f91;"
                                 "border-image:url(:/icons/home-icon-silhouette.png);"
                                 "border-radius: 6px;"
                                 "max-width: 50%;"
                                 "min-width: 50%;"
                                 "max-height: 50%;"
                                 "min-height: 50%;"
                                 "}");
    QPushButton *button_page_2 = new QPushButton();
    button_page_2->setStyleSheet("background-image:url(:/icons/mountains.jpg)");
    button_page_2->setObjectName("Button");


    //Buttons signals to switch to the different pages on the stacked widget.
    button_page_2->connect(button_page_2, SIGNAL(clicked()),stackedWidget, SLOT(changeIndex2()));

    // tell the player what buttons and videos are available
    player->setContent(&buttons, &videos);

    // create the main window and layout
    QWidget *home_page = new QWidget;
    QWidget *page_2 = new QWidget;

    //Add the button page to the home menu.
    rl->addWidget(button_page_2);

    //Page 1 set to the home page (rl)
    home_page->setLayout(rl);

    //Page Layout
    //Hold the whole page
    QHBoxLayout *page = new QHBoxLayout;

    //Left side of page
    QVBoxLayout *left = new QVBoxLayout;

    //Right side of page
    QVBoxLayout *right = new QVBoxLayout;

    //Holds the video player
    QVBoxLayout *playerr = new QVBoxLayout;

    //Holds the control buttons
    QHBoxLayout *buttonss = new QHBoxLayout;

    QWidget *scontent = new QWidget;
    QScrollArea *scroll = new QScrollArea;


    //control buttons
    controlButtons * play = new controlButtons();
    play->setStyleSheet("QPushButton {border: 2px solid #8f8f91;"
                        "border-image:url(:/icons/play.png);"
                        "border-radius: 6px;"
                        "max-width: 50%;"
                        "min-width: 50%;"
                        "max-height: 50%;"
                        "min-height: 50%;"
                        "}");
    controlButtons * light_mode = new controlButtons();
    light_mode->setStyleSheet("QPushButton {border: 2px solid #8f8f91;"
                              "border-image:url(:/icons/lightmode.png);"
                              "border-radius: 6px;"
                              "max-width: 50%;"
                              "min-width: 50%;"
                              "max-height: 50%;"
                              "min-height: 50%;"
                              "}");
    controlButtons * mute = new controlButtons();
    mute->setStyleSheet("QPushButton {border: 2px solid #8f8f91;"
                        "border-image:url(:/icons/volume-up.png);"
                        "border-radius: 6px;"
                        "max-width: 50%;"
                        "min-width: 50%;"
                        "max-height: 50%;"
                        "min-height: 50%;"
                        "}");

    //volume slider
    QSlider * volume = new QSlider(Qt::Horizontal);
    volume->setRange(0, 100);
    volume->setFixedWidth(200);
    volume->setValue(50);
    volume->connect(volume, SIGNAL(valueChanged(int)), player, SLOT(setVolume(int)));
    player->connect(player, SIGNAL(mutedChanged(bool)), volume,SLOT(setDisabled(bool)));
    volume->setStyleSheet("QSlider{margin-top: 5px;"
                             "margin-bottom: 5px; }"
                             "QSlider::groove:horizontal {border: 1px solid #1597E5; height: 8px;"
                             "background: #1597E5;"
                             "max-width: 50%;"
                             "margin: 2px 0;}"
                             "QSlider::handle:horizontal {"
                             "background: #69DADB;"
                             "border: 2px solid #193498;"
                             "width: 18px;"
                             "margin: -7px 0; "
                             "border-radius: 9px;"
                             "}");


    // sidebar widget
    QSlider * sliderbar = new QSlider(Qt::Horizontal);
    sliderbar->setRange(0,player->duration());
    sliderbar->connect(player,&QMediaPlayer::durationChanged, sliderbar, &QSlider::setMaximum);
    sliderbar->connect(player,&QMediaPlayer::positionChanged, sliderbar, &QSlider::setValue);
    sliderbar->connect(sliderbar,&QSlider::sliderMoved,player,&QMediaPlayer::setPosition);
    sliderbar->setStyleSheet("QSlider{margin-top: 5px;"
                             "margin-bottom: 5px; }"
                             "QSlider::groove:horizontal {border: 1px solid #1597E5; height: 8px;"
                             "background: #1597E5;"
                             "margin: 2px 0;}"
                             "QSlider::handle:horizontal {"
                             "background: #69DADB;"
                             "border: 2px solid #193498;"
                             "width: 18px;"
                             "margin: -7px 0; "
                             "border-radius: 9px;"
                             "}");

    //button functionality
    home_button_1->connect(home_button_1, SIGNAL(clicked()),stackedWidget, SLOT(changeIndex1()));
    play->connect(play, SIGNAL(clicked()), player, SLOT (playing()));
    play->connect(play,SIGNAL(clicked()),play,SLOT(isplaying()));
    light_mode->connect(light_mode,SIGNAL(clicked()),stackedWidget,SLOT(light_mode()));
    light_mode->connect(light_mode,SIGNAL(clicked()),light_mode,SLOT(lightmode()));
    mute->connect(mute, SIGNAL(clicked()), player, SLOT(mute()));
    mute->connect(mute, SIGNAL(clicked()), mute, SLOT(muted()));


    //adding buttons to buttonss layout
    buttonss->addWidget(home_button_1);
    buttonss->addWidget(play);
    buttonss->addWidget(light_mode);
    buttonss->addWidget(mute);
    buttonss->addWidget(volume);
    //adding player and sliderbar to playerr
    playerr->addWidget(videoWidget);
    playerr->addWidget(sliderbar);

    //adding playerr and buttonss to right
    right->addItem(playerr);
    right->addWidget(descriptortags);
    right->addItem(buttonss);
    //adding scroll area to left
    left->addWidget(scroll);

    //adding left and right to page
    page->addItem(left);
    page->addItem(right);

    //Add to the scroll area.
    scontent->setLayout(layout);
    scroll->setWidget(scontent);
    scroll->setWidgetResizable(true);
    scroll->setMinimumWidth(300);

    //Set layout of the pages.
    page_2->setLayout(page);
    //Set the pages ontop of the stacked widget.
    stackedWidget->addWidget(home_page);
    stackedWidget->addWidget(page_2);
    if(stackedWidget->currentIndex() == 0) {
        player->playing();
    }

    // showtime!
    stackedWidget->setWindowTitle("tomeo");
    stackedWidget->setMinimumSize(500, 400);
    stackedWidget->show();

    // wait for the app to terminate
    return app.exec();
}

