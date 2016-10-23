/**
 * mainwindow.cpp
 *
 *  Copyright 2016 by Joao Pedro Vieira Pereira Silva <jpvieirapereira@hotmail.com>
 *  Copyright 2015 by Victor Vieira Pereira Silva <victordoctorx@hotmail.com>
 *  Copyright 2014 by Marco Bueno <bueno.marco@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later.
 *  Some rights reserved. See COPYING, AUTHORS.
 *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include  "easter.h"


#define DEFAULT_BODY_TEXT \
            ui->textEdit->append( "");\
            ui->textEdit->append( "This sample demonstrate how to create and use database tables as ORM objects.");\
            ui->textEdit->append( "Database table, fields and access methods are defined in easter.cpp/.h files.");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    if( ConnectDB() )
        BuildData();

    connect(ui->dateEdit,SIGNAL(dateChanged(QDate)),this,SLOT(dateChanged(QDate)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::BuildData()
{

    Easter *easter = new Easter;

    easter->deleteAll();

    easter->setYear(2017);
    easter->setDate(QDate::fromString("16/04/2017","dd/MM/yyyy")); easter->setCarnival(easter->getDate().addDays(-47));easter->setCorpusChrist(easter->getDate().addDays(60));
    qDebug() << easter->getDate();
    easter->Save();
    delete easter; easter = new Easter;

    easter->setYear(2018);
    easter->setDate(QDate::fromString("01/04/2018","dd/MM/yyyy")); easter->setCarnival(easter->getDate().addDays(-47));easter->setCorpusChrist(easter->getDate().addDays(60));
    easter->Save();
    delete easter; easter = new Easter;

    easter->setYear(2019);
    easter->setDate(QDate::fromString("21/04/2019","dd/MM/yyyy")); easter->setCarnival(easter->getDate().addDays(-47));easter->setCorpusChrist(easter->getDate().addDays(60));
    easter->Save();
    delete easter; easter = new Easter;

    easter->setYear(2020);
    easter->setDate(QDate::fromString("12/04/2020","dd/MM/yyyy")); easter->setCarnival(easter->getDate().addDays(-47));easter->setCorpusChrist(easter->getDate().addDays(60));
    easter->Save();
    delete easter; easter = new Easter;

    easter->setYear(2021);
    easter->setDate(QDate::fromString("04/04/2021","dd/MM/yyyy")); easter->setCarnival(easter->getDate().addDays(-47));easter->setCorpusChrist(easter->getDate().addDays(60));
    easter->Save();
    delete easter; easter = new Easter;

    easter->setYear(2022);
    easter->setDate(QDate::fromString("17/04/2022","dd/MM/yyyy")); easter->setCarnival(easter->getDate().addDays(-47));easter->setCorpusChrist(easter->getDate().addDays(60));
    easter->Save();
    delete easter; easter = new Easter;

    easter->setYear(2023);
    easter->setDate(QDate::fromString("09/04/2023","dd/MM/yyyy")); easter->setCarnival(easter->getDate().addDays(-47));easter->setCorpusChrist(easter->getDate().addDays(60));
    easter->Save();
    delete easter; easter = new Easter;

    easter->setYear(2024);
    easter->setDate(QDate::fromString("31/03/2024","dd/MM/yyyy")); easter->setCarnival(easter->getDate().addDays(-47));easter->setCorpusChrist(easter->getDate().addDays(60));
    easter->Save();
    delete easter; easter = new Easter;

    easter->setYear(2025);
    easter->setDate(QDate::fromString("20/04/2025","dd/MM/yyyy")); easter->setCarnival(easter->getDate().addDays(-47));easter->setCorpusChrist(easter->getDate().addDays(60));
    easter->Save();
    delete easter;

    DEFAULT_BODY_TEXT

    setWindowTitle("Easter when?");
}

bool MainWindow::ConnectDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("test");
    db.setHostName("localhost");
    db.setUserName("user");
    db.setPassword("nopassword");

    if (!db.open())
    {
       qDebug() << "Connection Error!";
       return false;
    }
    return true;
}

void MainWindow::dateChanged(QDate current)
{
    ui->textEdit->clear();

    EasterList *easter = Easter::findByYear(current.year());
    if( easter)
    {

        ui->textEdit->append( "Easter: " + easter->at(0)->getDate().toString() );
        ui->textEdit->append( "Carnival: " + easter->at(0)->getCarnival().toString() );
        ui->textEdit->append( "Corpus Christ: " + easter->at(0)->getCorpusChrist().toString() );

        Easter::ReleaseList(easter);
    }
    else
    {
        ui->textEdit->append( "No entry found in easter table for the current year...");

    }

    DEFAULT_BODY_TEXT
}
