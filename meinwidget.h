
#include "zeichenfeld.h"

class meinWidget : public QWidget
{
    // Makro
    // wir binden Funktionen einer externen Bibliothek ein
    Q_OBJECT  // notwendig, da Slots enthalten sind

public:
    meinWidget(QWidget *parent = 0);

private:
    zeichenFeld *meinZeichenFeld;

    // erschaffe konstante Farb-Slots
    // mit slots können EVents wie Masusklick abgefangen werdenn
private slots:

    // funktionen um per Mausklick die Farbe des Brushes zu ändern
    void redColor(void)
    {
        meinZeichenFeld->setColor(Qt::red);
    }
    void greenColor(void)
    {
        meinZeichenFeld->setColor(Qt::green);
    }
    void setThickness(int value)
    {
        meinZeichenFeld->setThickness(value);
    }

    void saveFile(void);
    void loadFile(void);
    void start(void);
    void stop(void);
};
