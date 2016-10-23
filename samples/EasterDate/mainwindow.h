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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void dateChanged(QDate current);
private:
    Ui::MainWindow *ui;
    void BuildData();
    bool ConnectDB();
};

#endif // MAINWINDOW_H
