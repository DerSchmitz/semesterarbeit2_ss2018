#include <QtGui>
#include "zeichenFeld.h"

// CONSTRUCTOR
zeichenFeld::zeichenFeld(QWidget *parent)
     : QWidget(parent)
{

// definiere feste Größe des Zeichenfeldes
setFixedSize(500, 500);

// define background color
setPalette(QPalette(QColor(250, 250, 200)));
setAutoFillBackground(true);
setMouseTracking(false);



// erschaffe zeichenfeld, dass dependent auf einen Timer ein update startet!
timer=new QTimer(this);
connect(timer, SIGNAL(timeout()), this, SLOT(update()));

// set default values for incremental timing
increment=0;
phase=0;


// set default lives for the avatar
lives = 3;

}

/* DESTRUCTOR */
zeichenFeld::~zeichenFeld()
{

// erschaffe vector von Punkt-struct
                            // erschaffe iterator und iteriere ihn
for (vector<struct myPoint *>::iterator pos=points.begin();pos!=points.end();pos++)
    delete *pos;
}


/* PAINT EVENT */
void zeichenFeld::paintEvent(QPaintEvent * )
{
// create painter
QPainter painter;
painter.begin( this );


/* CREATE DRAWING-OBJECTS*/
// falls der avatar zum Zeitpunkt des Zeichnens noch nicht bespielt sein
if (avatar==NULL) {
    // bespiele ihn mit den default-werten,
    avatar = new zeichenFeld;

    // sollte der avatar bereits gezeichnet sein
} else {
    // bespiele ihn nicht neu, da er evtl. seitdem manipuliert wurde
}

// falls das Hagelkorn zum Zeitpunkt des Zeichnens noch nicht bespielt sein
if (hagelKoerner==NULL) {
    // bespiele ihn mit den default-werten,
    hagelKoerner = new zeichenFeld;
    // sollte das hagelkorn bereits gezeichnet sein
}

// create points for Hagel
                            // set maximal amount of Hagel
if (hagelKoerner->points.size()<40) {
    struct myPoint *point;
    point=new struct myPoint;

    // calculate random x-position of
    int random_integer = rand()%500;

    point->point.setX(0 + random_integer);
    point->point.setY(0);
    hagelKoerner->points.push_back(point);
}

// create hearts object
if (hearts==NULL) {
    // bespiele ihn mit den default-werten,
    hearts = new zeichenFeld;
}

// set points for health-symbols
for (int i=0;i< avatar->lives;i++){

    struct myPoint *point;
    point=new struct myPoint;
    point->point.setX(400 + (i*25));
    point->point.setY(0);
    hearts->points.push_back(point);

}

// display Highscore
QString numberOfPoints = QString::number(counter);
if (avatar->lives>0) {
    painter.drawText(rect(), Qt::AlignLeft, numberOfPoints);
} else {
    painter.drawText(rect(), Qt::AlignRight, "Game OVER"  );
    painter.drawText(rect(), Qt::AlignLeft , numberOfPoints );
}



if (hagelKoerner->points.size()>0)
   {

    // WICHTIG!! DEFINIERE WELCHER VEKTOR ITERIERT WERDEN SOLL!
    // Punkteliste des Hagelkorns durchiterieren
       pos=hagelKoerner->points.begin();


        for(;;)
          {

          // wenn pos am ende angelangrt ist, beende for-loop
          if (pos==hagelKoerner->points.end()) break;
          // ansonsten
                // erschaffe stift mit der in dem Start-Punkt definierten Farbe und Thickness

          // PLAN TIMED EVENTS!!!
          if (increment)
              switch(phase)
              {
              case 0:
                  //cout << "(*pos)->point.y()<500): " << (*pos)->point.y() << endl;
                  if ((*pos)->point.y()<500) (*pos)->point.setY((*pos)->point.y()+5);
                  else phase=1;
                  break;
              case 1:
                  // (*pos)->point.setY(0);
                  //(*pos)->point.setY(660);
                   //pos++;
                  //*pos=NULL;
                  //hagelKoerner->points.erase(hagelKoerner->points.begin()+1    );
                  hagelKoerner->points.erase(hagelKoerner->points.begin()    );
                  //cout << "POINT DELETED "<< endl;
                  phase=0;
                  break;
              }


          // zeichne Hagelkorn

          if (*pos!=NULL) {
                      painter.drawEllipse((*pos)->point.x(),(*pos)->point.y(), 25,25);
          }

          // erhöhe Punkte-Counter
          if(avatar->lives>0) {
            counter++;
          }

          // setze letzePos gleich momentane Position
          letztePos = pos;
          //dann iteriere pos laangsam
         pos++;

          //painter.setPen( QPen((*start)->color, (*start)->width)  );
          //painter.drawLine((*start)->point,(*pos)->point);
        }






    }



// DRAW HEALTH

// paint 3 empty hearts at all times
painter.drawEllipse(400,0, 25,18);
painter.drawEllipse(425,0, 25,18);
painter.drawEllipse(450,0, 25,18);

if (hearts->points.size()>0)
   {

    // WICHTIG!! DEFINIERE WELCHER VEKTOR ITERIERT WERDEN SOLL!
    // Punkteliste der hearts durchiterieren
       pos=hearts->points.begin();


        for(;;)
          {
            int counterPos;

          // wenn pos am ende angelangrt ist, beende for-loop
          if (pos==hearts->points.end()) break;

          // ansonsten
                // erschaffe stift mit der in dem Start-Punkt definierten Farbe und Thickness
          // zeichne hearts

          if (*pos !=NULL ) {
              //if (*letztePos !=NULL ) {painter.drawEllipse((*letztePos)->point.x(),(*letztePos)->point.y(), 25,18)};
              //cout << (*pos)->point.x() << "  " << (*pos)->point.y() << endl;

              QPainterPath path;
              path.addEllipse((*pos)->point.x(),(*pos)->point.y(), 25,18);

              painter.fillPath(path, Qt::red);
              painter.drawPath(path);

          }


          // setze letzePos gleich momentane Position
          letztePos = pos;
          *pos=NULL;

          // UNSAUBER - LISTENpunkt bleibt erhalten
          //hearts->points.erase(hearts->points.begin()+counterPos);

          //dann iteriere pos laangsam
         pos++;
            counterPos++;

          //painter.setPen( QPen((*start)->color, (*start)->width)  );
          //painter.drawLine((*start)->point,(*pos)->point);
         }

    }


if (avatar->points.size()>0)
   {
    // WICHTIG!! DEFINIERE WELCHER VEKTOR ITERIERT WERDEN SOLL!
    // Punkteliste des Avatars durchiterieren

    pos=avatar->points.begin();


        for(;;)
          {

          // wenn pos am ende angelangrt ist, beende for-loop
          if (pos==avatar->points.end()) break;
          // ansonsten
                // erschaffe stift mit der in dem Start-Punkt definierten Farbe und Thickness
          // zeichne avatar

          if (*pos !=NULL ) {

              painter.drawRect((*pos)->point.x(),(*pos)->point.y(), 25,25);

              //draw inner line of avatar
              struct myPoint *point;
              point=new struct myPoint;
              point->point.setX((*pos)->point.x() + 25);
              point->point.setY(500);
              painter.drawLine((*pos)->point , point->point );







               int avatarPositionX  = (*pos)->point.x();
               int avatarPositionY  = 475;
              // IMPLEMENT COLLISION-LOGIC!!!
               posHagel=hagelKoerner->points.begin();
              for(;;)
                {


                // wenn posHagel am ende angelangrt ist, beende for-loop
                if (posHagel==hagelKoerner->points.end()) break;
                // ansonsten
                      // erschaffe stift mit der in dem Start-Punkt definierten Farbe und Thickness


                bool collisionHappened = false;
                for (int j=0; j<25; j++) {


                    for (int n=0; n<25; n++) {
                            if( avatarPositionX + j ==(*posHagel)->point.x()+n and avatarPositionY ==(*posHagel)->point.y() ){
                                cout << "COLLISION - YOU LOST 1 LIVE"<< endl;
                                avatar->lives--;

                                collisionHappened = true;
                                break;
                            }

                        if (collisionHappened == true   ) { break; }


                    }
                }

                posHagel++;
              }
              //  COLLISION-LOGIK - ENDE!!!
          }



          // setze letzePos gleich momentane Position
          letztePos = pos;
          //dann iteriere pos laangsam
         pos++;

        }
    }else {
            // create reference-point of avatar for the first time
            struct myPoint *point;
            point=new struct myPoint;
            point->point.setX(225);
            point->point.setY(475);
            avatar->points.push_back(point);
        }

    painter.end();

}


// define keyboard-Listener
void zeichenFeld::keyPressEvent( QKeyEvent *keyboardEvent)
{
    if(keyboardEvent->key() == Qt::Key_A){

        avatar->x_koordinate -= 10;

       /* QMessageBox::warning(this, tr("Objektfehler"),
                             tr("Folgender Objekttyp ist unbekannt: "),QMessageBox::Ok);*/
    }
     if (keyboardEvent->key()== Qt::Key_D) {

        avatar->x_koordinate += 10;

    }

    //update();


}





// define mouse-Listener
void zeichenFeld::mousePressEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton)
    {
                // der breitengrad  definiert sich über
                int x_temp = (*letztePos)->point.x();
                x_temp -= 25;

                cout <<  x_temp << endl;
                (*letztePos)->point.setX(x_temp);
                // Punkt wird NICHT in die List des Avatars geschoben, damit kein neuer Kreis erzeugt wird!!!
                //avatar->points.push_back(point);

    }

    if (event->button() == Qt::RightButton)
    {
        // der breitengrad  definiert sich über
        int x_temp = (*letztePos)->point.x();
        x_temp += 25;

        cout <<  x_temp << endl;
        (*letztePos)->point.setX(x_temp);

    }

}

// SERIALIZE METHODE
void zeichenFeld::serialize(QFile &file)
{
    // we use Text Outstream to print text in file
    QTextStream out(&file);

    // definiere "Header" des Dokuments um sicher zusein, dass das Format stimmt
    out << "Ismael" << endl;
    cout << "Ismael" << endl; // testausgabe in Konsole

    // WICHTIG!! DEFINIERE WELCHER VEKTOR ITERIERT WERDEN SOLL!
    // Punkteliste des Avatars durchiterieren
       pos=avatar->points.begin();
       for (;;) {

        // stoppe iteration, wenn am Ende angelangt
        if (pos==avatar->points.end()) break;

        // PRINT OUT
       // marker "a" gefolgt von x-koordinate gefolgt von y-koordinate getrennt durch ein " "
       out  << "a "
            << (*pos)->point.x()<< " " << (*pos)->point.y() << endl;
       cout  << "a "
            << (*pos)->point.x()<< " " << (*pos)->point.y() << endl;

      // iteriere, damit etwaige weitere Punkte ebenfalls gespeicher werden können
      pos++;

       }

       // WICHTIG!! DEFINIERE WELCHER VEKTOR ITERIERT WERDEN SOLL!
       // Punkteliste des hagelkorns durchiterieren
          pos=hagelKoerner->points.begin();
          for (;;) {

           // stoppe iteration, wenn am Ende angelangt
           if (pos==hagelKoerner->points.end()) break;

           // PRINT OUT
          // marker "h" gefolgt von x-koordinate gefolgt von y-koordinate getrennt durch ein " "

           out  << "h "
               << (*pos)->point.x()<< " " << (*pos)->point.y() << endl;
          cout  << "h "
               << (*pos)->point.x()<< " " << (*pos)->point.y() << endl;

         // iteriere, damit etwaige weitere Punkte ebenfalls gespeicher werden können
         pos++;

          }

             // save counter in file
             out  << "c "
                 << counter << endl;

             // save lives of avatar in file
             out  << "l "
                 << avatar->lives << endl;

}


// DESERIALIZE METHODE
void zeichenFeld::deserialize(QFile &file)
{
    /* TOOLS */
    // wir brauchen Punkte, um Koordinaten an die paintFucntion zu überführen
    struct myPoint *point;
    // wir brauchen einen char um das Textformat abzutasten
    char c;
    // wir brauchen einen String um den Header der Datei abzufragen
    QString test;
    // wir brauchen integer, um die x- und y-koordinaten aus dem DOkument zu extrahieren
    int x, y;
    //int red, green, blue, x, y;
    bool isFirstPositionAlreadyOverwritten =false;


    QTextStream in(&file);



    /* PRÜFE FORMAT-HEADER*/
    // lese erste zeile in string
    in >> test;
    // prüfe string
    if (test != "Ismael")
    {
        QMessageBox::warning(this, tr("Formatfehler"),
                             tr("Das ist keine Zeichnungsdatei!"),QMessageBox::Ok);
        return;
    }
    in >> c;  // konsumiere überschüssigen Line-Break

    /* PRÜFE FORMAT-HEADER - ENDE */


    /*BEGIN  DATAEXTRACTION */
    // lese DOkument zeilenweise ein !!!
    while (in.status() == QTextStream::Ok)
    {

        // iteriere Lines
        for(;;) {
            // spiele Zeichen zeichenweise in vaariable c ein
            in >> c;
            // haben wir fertig gelesen?
            if (in.status() == QTextStream::ReadPastEnd) break;
            cout << "Test-Char lautet: " << c <<endl;

            // Welches Objekt wird gerade gelesen??
            if(c=='a'){

                       // extrahiere x-koordinate
                       in >> x;
                       // extrahiere y-koordinate
                       in >> y;


                       if(isFirstPositionAlreadyOverwritten==false) {
                           // WICHTIG!! DEFINIERE WELCHER VEKTOR ITERIERT WERDEN SOLL!
                           // Punkteliste des Avatars durchiterieren
                            pos=avatar->points.begin();

                           (*pos)->point.setX(x);
                           (*pos)->point.setY(y);
                           cout << "Koordinaten reset"<< endl;

                           isFirstPositionAlreadyOverwritten = true;

                       } else {
                           point = new struct myPoint;
                           point->point.setX(x);
                           point->point.setY(y);
                           avatar->points.push_back(point);
                           cout << " PUNKT WURDE GEPUSHT!!"<< endl;
                       }

                       //letztePos = pos;
                         // iteriere, damit etwaige weitere Punkte ebenfalls gespeicher werden können
                       // pos++;

                         in >> c; // konsumiere überschüssigen Line-Break


            }  else if (c=='h'){
                // extrahiere x-koordinate
                in >> x;
                // extrahiere y-koordinate
                in >> y;


                    point = new struct myPoint;
                    point->point.setX(x);
                    point->point.setY(y);
                    hagelKoerner->points.push_back(point);
                    cout << " PUNKT WURDE GEPUSHT!!"<< endl;


                  in >> c; // konsumiere überschüssigen Line-Break


             }  else if (c=='c'){
                // extrahiere c-koordinate
                in >> counter;


                in >> c; // konsumiere überschüssigen Line-Break


             }  else if (c=='l'){
                // extrahiere c-koordinate
                in >> avatar->lives;


                in >> c; // konsumiere überschüssigen Line-Break


             }  else {
                // breche Aktion ab
                QMessageBox::warning(this, tr("Objektfehler"),
                                     tr("Folgender Objekttyp ist unbekannt: ") + c,QMessageBox::Ok);
                return;
            }




        }



// Line wurde fertig gelesen
 }


    update();
}
