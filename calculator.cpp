#include "calculator.h"
#include "ui_calculator.h"

using namespace std;

double calcVal = 0.0;
double resultVal = 0.0;
int mathOperationKey = 0;

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

        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumButtonPressed()));

    }

    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualsButtonPressed()));
    connect(ui->Clear, SIGNAL(released()), this, SLOT(Clear()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumButtonPressed()
{
    if (resultVal != 0.0)
        Clear();

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
    calcVal = ui->Display->text().toDouble();

    QString butVal = ((QPushButton*)sender())->text();

    mathOperationKey = butVal.toUtf8().constData()[0];

    ui->Display->setText(butVal);
}

void Calculator::EqualsButtonPressed()
{
    double displayVal = ui->Display->text().toDouble();

    if (mathOperationKey == 0)
        return;

    switch (mathOperationKey)
    {
        case 43:
            resultVal = calcVal + displayVal;
            break;
        case 45:
            resultVal = calcVal - displayVal;
            break;
        case 42:
            resultVal = calcVal * displayVal;
            break;
        case 47:
            resultVal = calcVal / displayVal;
            break;
        default:
            break;
    }

    ui->Display->setText(QString::number(resultVal));
}

void Calculator::ChangeSignButtonPressed()
{
}

void Calculator::Clear()
{
    calcVal = 0.0;
    resultVal = 0.0;
    mathOperationKey = 0;
    ui->Display->setText(QString::number(calcVal));
}

