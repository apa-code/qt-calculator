#include "calculator.h"
#include "ui_calculator.h"

double calcVal = 0.0;
bool divTrigger = false;
bool mulTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(calcVal));

    QPushButton* numButtons[10];
    for(unsigned int i = 0; i < sizeof(numButtons)/sizeof(numButtons[0]); i++)
    {
        QString butName = "Button" + QString::number(i);

        numButtons[i] = Calculator::findChild<QPushButton*>(butName);

        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));

    }
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumButtonPressed()
{
    QPushButton* button = (QPushButton*)sender();

    QString butVal = button->text();
    QString displayVal = ui->Display->text();

    if ((displayVal.toDouble() == 0.0))
    {
        ui->Display->setText(butVal);
    }
    else
    {
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();

        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }
}

void Calculator::MathButtonPressed()
{
    divTrigger = false;
    mulTrigger = false;
    addTrigger = false;
    subTrigger = false;

    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();

    QPushButton* button = (QPushButton*)sender();
    QString butVal = button->text();

    if (QString::compare(butVal, "/", Qt::CaseInsensitive) == 0)
    {
        divTrigger = true;
    }
    else if (QString::compare(butVal, "*", Qt::CaseInsensitive) == 0)
    {
        mulTrigger = true;
    }
    else if (QString::compare(butVal, "+", Qt::CaseInsensitive) == 0)
    {
        addTrigger = true;
    }
    else
    {
        subTrigger = true;
    }

    ui->Display->setText("");
}

void Calculator::EqualsButtonPressed()
{
}

void Calculator::ChangeSignButtonPressed()
{
}

