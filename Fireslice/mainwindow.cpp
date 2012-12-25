#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "view.h"
#include "model.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    View *view = new View(0);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(view);

    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);

    centralWidget()->setLayout(mainLayout);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}
