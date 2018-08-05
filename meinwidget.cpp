#include <QtGui>

#include "meinWidget.h"




meinWidget::meinWidget(QWidget *parent)
    : QWidget(parent)
{
    // quit button
    QPushButton *quit = new QPushButton(tr("Ende"));
    quit->setFont(QFont("Times", 18, QFont::Bold));
    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    // set red button
                                        // mit text-red
    QPushButton *redButton = new QPushButton(tr("Rot"));
    redButton->setFont(QFont("Times", 18, QFont::Bold));
    // change
    connect(redButton, SIGNAL(clicked()), this, SLOT(redColor()));
    QPushButton *greenButton = new QPushButton(tr("Grün"));
    greenButton->setFont(QFont("Times", 18, QFont::Bold));
    connect(greenButton, SIGNAL(clicked()), this, SLOT(greenColor()));
    /*QSlider *slider = new QSlider(Qt::Horizontal,this);
    slider->setFont(QFont("Times", 18, QFont::Bold));
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setThickness(int)));*/

    /* Use additional Buttons for saving!*/
    // erschaffe button objekt
                                        // mit string "Sichern"
    QPushButton *saver = new QPushButton(tr("Sichern"));
    // set styles
    saver->setFont(QFont("Times", 18, QFont::Bold));
    // connect onclick-Function
    connect(saver, SIGNAL(clicked()), this, SLOT(saveFile()));

    QPushButton *loader = new QPushButton(tr("Laden"));
    loader->setFont(QFont("Times", 18, QFont::Bold));
    connect(loader, SIGNAL(clicked()), this, SLOT(loadFile()));


    // START - STOP
    QPushButton *startButton = new QPushButton(tr("Start"));
    startButton->setFont(QFont("Times", 18, QFont::Bold));
    connect(startButton, SIGNAL(clicked()), this, SLOT(start()));

    QPushButton *stopButton = new QPushButton(tr("Pause"));
    stopButton->setFont(QFont("Times", 18, QFont::Bold));
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stop()));





    meinZeichenFeld = new zeichenFeld;


    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(quit, 0, 0);
    /*gridLayout->addWidget(redButton, 1, 0);
    gridLayout->addWidget(greenButton, 2, 0);
    gridLayout->addWidget(slider, 3, 0);*/
    gridLayout->addWidget(saver, 1, 0);
    gridLayout->addWidget(loader, 2, 0);

    gridLayout->addWidget(startButton, 3, 0);
    gridLayout->addWidget(stopButton, 4, 0);


    gridLayout->addWidget(meinZeichenFeld, 0, 1, 4, 1);
    gridLayout->setColumnStretch(1, 10);
    setLayout(gridLayout);


}









// implement save function
void meinWidget::saveFile(void)
{
    QFileDialog dialog(this);
    QString fileName;
    QFile file;

    dialog.setFileMode(QFileDialog::AnyFile);
    fileName = dialog.getSaveFileName(this,
                                      tr("Speichern als"), ".", tr("Zeichnungen (*.myz)"));

    if (fileName.isNull()==false)
    {
        file.setFileName(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Dateifehler"),
                                 tr("Folgende Datei kann nicht verwendet werden: ") + fileName,QMessageBox::Ok);
        }

        meinZeichenFeld->serialize(file);
        file.close();
        return;
    }
}

// implement load function

void meinWidget::loadFile(void)
{
    QFileDialog dialog(this);
    QString fileName;
    QFile file;

    dialog.setFileMode(QFileDialog::AnyFile);
    fileName = dialog.getOpenFileName(this,
                                      tr("Speichern als"), ".", tr("Zeichnungen (*.myz)"));

    if (fileName.isNull()==false)
    {
        file.setFileName(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Dateifehler"),
                                 tr("Folgende Datei kann nicht geöffnet werden: ") + fileName,QMessageBox::Ok);
        }

        meinZeichenFeld->deserialize(file);
        file.close();
        return;
    }
}


void meinWidget::start(void)
{
    meinZeichenFeld->startTimer();
}

void meinWidget::stop(void)
{
    meinZeichenFeld->stopTimer();
}




