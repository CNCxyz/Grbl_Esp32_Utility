/****************************************************************************
**
** Copyright (C) 2021 AJ Quick <https://cnc.xyz>
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QMessageBox>
#include <QApplication>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    struct Settings {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
    };

    struct GrblSettings {
        QString radioMode;
        QString wifiSSID;
        QString wifiPassword;
        QString wifiIPMode;
        QString wifiIP;
        QString apSSID;
        QString apPassword;
        QString apIP;
        QString apChannel;
    };

    void makeConnection(QSerialPort *port);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setPort(QSerialPort *port);

protected:
    QString readAndWrite(QString input);
private slots:
    void on_exitButton_clicked();
    void on_connectionButton_clicked();
    void on_updateButton_clicked();
    void on_Input_changed();

private:
    Ui::MainWindow *ui;
    QSerialPort *m_port;
    Settings currentSettings;
    GrblSettings grblSettings;
    GrblSettings changedSettings;
    void updateSettings();
    void disableForms();
    void refreshSerialData();
    bool unsavedChanges = false;
    bool updateInProgress = false;
    void updateApply();
    void enableForms();
    void updateForms();
    bool unsavedNotice();
    bool waitForReady(QSerialPort *port, int timeout);
};
#endif // MAINWINDOW_H
