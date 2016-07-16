#include "guitest.h"
#include "ui_guitest.h"
#include <QString>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QRect>
#include <QDesktopWidget>
#include <QSignalMapper>
#include <QFile>
#include <QTextStream>


int isNormalizationFilled = 0,
isSpinBoxFilled = 0,
normalizationBtnCnt = 0,
spinArray[16] = {0,0,0,0,
                 0,0,0,0,
                 0,0,0,0};

QString pythonProgrmaFile = "";
QString outputDirectory = "";
QFile file("pls_sm_output.py");
QTextStream output(&file);

GuiTest::GuiTest (QWidget *parent){
    QMainWindow(parent), ui(new Ui::GuiTest){
        ui->setupUi(this);
        setSizeOfWindow();
        setQSpinWidgets();
        setOutputFile();
    }
}

GuiTest::~GuiTest()(){
    delete ui;
}

void setSizeOfWindow(){
    QRect currentWindowSize = QApplication::desktop()->screenGeometry();
    int height = currentWindowSize.height();
    this->resize(this->width(), height*0.9);
    for (int i = 0; i < norm_size; i++){        //setting up visibility
        setSpinleftVisible(i, false);
        setSpinrightVisible(i, false);
        setLabelsVisible(i, false);
    }
}

void GuiTest::setQSpinWidgets(){
    QList<QSpinBox*> allChildSpinBoxes = findChildren<QSpinBox*>();
    QSignalMapper* signalMapper = new QSignalMapper(this);
    QSpinBox oneChildSpinbox;
    foreach(oneChildSpinbox, allChildSpinBoxes){
        connect(oneChildSpinbox, SIGNAL(valueChanged(int)), signalMapper, SLOT(map()));
        signalMapper->setMapping(oneChildSpinbox, oneChildSpinbox);
    }
    connect(signalMapper, SIGNAL(mapped(QWidget*)), this, SLOT(getSpinboxValue(QWidget*)));
}

void GuiTest::SetupOutFile(){
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream output(&file);
    output << "from pysat.spectral.spectral_data import spectral_data\n";
    output << "from pysat.regression.pls_sm import pls_sm\n";
    output << "import pandas as pd\n";
}

void GuiTest::setLabelAndSpinVisible(int index, bool visible){
    int arraySize = 7;
    QLabel* labels[arraySize] = {ui->norm_label_2,
                                 ui->norm_label_3,
                                 ui->norm_label_4,
                                 ui->norm_label_5,
                                 ui->norm_label_6,
                                 ui->norm_label_7,
                                 ui->norm_label_8};
    QSpinBox* spinBoxR[arraySize] = {ui->norm_spinBox_2,
                                     ui->norm_spinBox_3,
                                     ui->norm_spinBox_4,
                                     ui->norm_spinBox_5,
                                     ui->norm_spinBox_6,
                                     ui->norm_spinBox_7,
                                     ui->norm_spinBox_8};
    QSpinBox* spinBoxL[arraySize] = {ui->norm_spinBox_10,
                                     ui->norm_spinBox_11,
                                     ui->norm_spinBox_12,
                                     ui->norm_spinBox_13,
                                     ui->norm_spinBox_14,
                                     ui->norm_spinBox_15,
                                     ui->norm_spinBox_16
                                    };
    labels[index]->setVisible(visible);
    spinBoxL[index]->setVisible(visible);
    spinBoxR[index]->setVisible(visible);
}

void GuiTest::on_maskFileButton_clicked(){

}

void GuiTest::on_unknownDataButton_clicked(){

}

void GuiTest::on_fullDataBaseButton_clicked(){

}

void GuiTest::on_outPutLocation_clicked(){

}

void GuiTest::on_pythonButton_clicked(){

}

void GuiTest::on_NormValuebutton_clicked(){

}

int GuiTest::getSpinValue(){
    QSpinBox* spinValue = (QSpinBox*)widgetSpinValue;
    int valueofSpin = spinValue->value();
    return value;
}
