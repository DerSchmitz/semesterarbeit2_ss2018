#include <iostream>
using namespace std;

#include <vector>
#include <QWidget>
// add QFile for handling of saves - INCLUDES LOAD AND SAVE FUNCTION!!!
#include <QFile>
// nur notwendig, wenn Qt 5:
#include <QPushButton>
#include <QGridLayout>
#include <QSlider>
#include <QFileDialog>
#include <QMessageBox>
#include <QKeyEvent>
//Ende Qt 5
#include <QTimer>
#include <QtGui>
#include <QtCore>

#include <QApplication>



struct myPoint
   {
   QPoint point;
   int width;
   QColor color;
   } ;


class zeichenFeld : public QWidget
{

public:
    zeichenFeld(QWidget *parent = 0);
    ~zeichenFeld();

    // erschaffe objekt für avatar
    zeichenFeld *avatar = NULL;
    //erschaffe objekt für Hagelkörner
    zeichenFeld *hagelKoerner = NULL;
    zeichenFeld *hearts = NULL;


    void setColor(QColor useColor) { color=useColor; }
    void setThickness(int useWidth) { width=useWidth; }


    void startTimer(void) { timer->start(27); increment=1; };

    void stopTimer(void) { timer->stop(); increment=-1; };


    // serialization-funktionen:
    void serialize(QFile &file);
    void deserialize(QFile &file);



private:
    vector<struct myPoint *> points;
    // erschaffe 2 Iteratoren
    vector<struct myPoint *>::iterator pos,letztePos, posHagel, letztePosHagel;

    QColor color;
    int width;

    int x_koordinate;
    //int y_koordinate;

    // counter for score
    int counter;

    // counter for lives of the avatar
    int lives;

    // TIMER VARIABLES

    QTimer *timer;
  /*  int lastX;
    int lastY;*/
    int increment;
    int phase;


protected:
        void paintEvent(QPaintEvent* event);
  //  void mouseMoveEvent( QMouseEvent* event);
        void mousePressEvent(QMouseEvent* event);

    // Erschaffe Event für Keyboard-Eingabe
        void keyPressEvent(QKeyEvent* keyboardEvent);
};

