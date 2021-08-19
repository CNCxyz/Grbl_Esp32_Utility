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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_port(nullptr)
{
    ui->setupUi(this);
    disableForms();
    updateApply();

    connect(ui->wifiModeButton, SIGNAL(clicked()), this, SLOT(on_Input_changed()));
    connect(ui->apModeButton, SIGNAL(clicked()), this, SLOT(on_Input_changed()));
    connect(ui->staticModeButton, SIGNAL(clicked()), this, SLOT(on_Input_changed()));
    connect(ui->dhcpModeButton, SIGNAL(clicked()), this, SLOT(on_Input_changed()));
    connect(ui->ssidInput, SIGNAL(textChanged(const QString &)), this, SLOT(on_Input_changed()));
    connect(ui->passwordInput, SIGNAL(textChanged(const QString &)), this, SLOT(on_Input_changed()));
    connect(ui->ipAddressInput, SIGNAL(textChanged(const QString &)), this, SLOT(on_Input_changed()));
    connect(ui->apChannelInput, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(on_Input_changed()));
    connect(ui->ipGatewayInput, SIGNAL(textChanged(const QString &)), this, SLOT(on_Input_changed()));
    connect(ui->ipNetmaskInput, SIGNAL(textChanged(const QString &)), this, SLOT(on_Input_changed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateApply(){
    if(unsavedChanges == true){
        ui->updateButton->setEnabled(true);
    }else{
        unsavedChanges = false;
        ui->updateButton->setDisabled(true);
    }
}

void MainWindow::on_exitButton_clicked()
{
        if(unsavedNotice("quit")){
          // Quit
          if(m_port->isOpen())
            m_port->close();
          close();
          qApp->quit();
        }
}

void MainWindow::setPort(QSerialPort *port)
{
    m_port = port;
}

void MainWindow::updateSettings()
{
    if (m_port == nullptr) {
        m_port = new QSerialPort(this);
    }

    if(ui->serialPortInfoListBox->count() > 0){

        currentSettings.name = ui->serialPortInfoListBox->itemData(ui->serialPortInfoListBox->currentIndex()).toStringList().first();
        currentSettings.baudRate = ui->baudRateBox->baudRate();
        currentSettings.stringBaudRate = QString::number(currentSettings.baudRate);
        makeConnection(m_port);

    }

}
void MainWindow::makeConnection(QSerialPort *port)
{
    port->setPortName(ui->serialPortInfoListBox->itemData(ui->serialPortInfoListBox->currentIndex()).toString());
    port->setBaudRate(ui->baudRateBox->baudRate());
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);
    setPort(port);
}

void MainWindow::disableForms(){
    ui->connectionLabel->setDisabled(true);
    ui->ipAddressLabel->setDisabled(true);
    ui->ssidLabel->setDisabled(true);
    ui->passwordLabel->setDisabled(true);
    ui->modeLabel->setDisabled(true);
    ui->apChannelLabel->setDisabled(true);
    ui->ipAddressInput->setDisabled(true);
    ui->ssidInput->setDisabled(true);
    ui->passwordInput->setDisabled(true);
    ui->apChannelInput->setDisabled(true);
    ui->connectionInput->setDisabled(true);
    ui->modeInput->setDisabled(true);
    ui->updateButton->setDisabled(true);
    ui->ipNetmaskLabel->setDisabled(true);
    ui->ipNetmaskInput->setDisabled(true);
    ui->ipGatewayLabel->setDisabled(true);
    ui->ipGatewayInput->setDisabled(true);
    unsavedChanges = false;
}

void MainWindow::enableForms(){
    ui->connectionLabel->setEnabled(true);
    ui->ipAddressLabel->setEnabled(true);
    ui->ssidLabel->setEnabled(true);
    ui->passwordLabel->setEnabled(true);
    ui->modeLabel->setEnabled(true);
    ui->apChannelLabel->setEnabled(true);
    ui->ipAddressInput->setEnabled(true);
    ui->ssidInput->setEnabled(true);
    ui->passwordInput->setEnabled(true);
    ui->apChannelInput->setEnabled(true);
    ui->connectionInput->setEnabled(true);
    ui->modeInput->setEnabled(true);
    ui->ipNetmaskLabel->setEnabled(true);
    ui->ipNetmaskInput->setEnabled(true);
    ui->ipGatewayLabel->setEnabled(true);
    ui->ipGatewayInput->setEnabled(true);
}

void MainWindow::updateForms(){

    updateInProgress = true;

    if(changedSettings.radioMode == "STA"){
        ui->wifiModeButton->setChecked(true);
        ui->apModeButton->setChecked(false);

        ui->ssidInput->setText(changedSettings.wifiSSID);
        ui->passwordInput->setText(changedSettings.wifiPassword);
        ui->ipAddressInput->setText(changedSettings.wifiIP);

        ui->ipGatewayInput->setText(changedSettings.wifiGateway);
        ui->ipNetmaskInput->setText(changedSettings.wifiNetmask);

    }else if(changedSettings.radioMode == "AP"){
        ui->wifiModeButton->setChecked(false);
        ui->apModeButton->setChecked(true);

        ui->ssidInput->setText(changedSettings.apSSID);
        ui->passwordInput->setText(changedSettings.apPassword);
        ui->ipAddressInput->setText(changedSettings.apIP);

        ui->ipGatewayInput->setText("");
        ui->ipNetmaskInput->setText("");

    }else{
        //Bluetooth
    }

    if(changedSettings.wifiIPMode == "DHCP"){
        ui->dhcpModeButton->setChecked(true);
        ui->staticModeButton->setChecked(false);
    }else if(changedSettings.wifiIPMode == "Static"){
        ui->dhcpModeButton->setChecked(false);
        ui->staticModeButton->setChecked(true);
    }else{
        //ERROR!
    }

    ui->apChannelInput->setCurrentText(changedSettings.apChannel);

    if(ui->wifiModeButton->isChecked()){

        if(ui->dhcpModeButton->isChecked()){
            ui->ipAddressLabel->setDisabled(true);
            ui->ipAddressInput->setDisabled(true);
            ui->ipNetmaskLabel->setDisabled(true);
            ui->ipNetmaskInput->setDisabled(true);
            ui->ipGatewayLabel->setDisabled(true);
            ui->ipGatewayInput->setDisabled(true);
        }else if(ui->staticModeButton->isChecked()){
            ui->ipAddressLabel->setEnabled(true);
            ui->ipAddressInput->setEnabled(true);
            ui->ipNetmaskInput->setEnabled(true);
            ui->ipGatewayInput->setEnabled(true);
            ui->ipNetmaskLabel->setEnabled(true);
            ui->ipGatewayLabel->setEnabled(true);
        }else{
            //Error?
        }

        ui->apChannelLabel->setDisabled(true);
        ui->apChannelInput->setDisabled(true);
        ui->modeInput->setEnabled(true);
        ui->dhcpModeButton->setEnabled(true);
        ui->staticModeButton->setEnabled(true);

    }else if(ui->apModeButton->isChecked()){
        ui->apChannelLabel->setEnabled(true);
        ui->apChannelInput->setEnabled(true);
        ui->modeInput->setDisabled(true);
        ui->dhcpModeButton->setDisabled(true);
        ui->staticModeButton->setDisabled(true);
        ui->ipAddressLabel->setEnabled(true);
        ui->ipAddressInput->setEnabled(true);
        ui->ipNetmaskLabel->setDisabled(true);
        ui->ipNetmaskInput->setDisabled(true);
        ui->ipGatewayLabel->setDisabled(true);
        ui->ipGatewayInput->setDisabled(true);
    }else{
        //Bluetooth
    }

    updateInProgress = false;

}


void MainWindow::refreshSerialData(){

    grblSettings = {};

        //Grab Current Settings
        grblSettings.radioMode = readAndWrite("$Radio/Mode");
        grblSettings.wifiSSID = readAndWrite("$Sta/SSID");
        grblSettings.wifiPassword = readAndWrite("$Sta/Password");
        grblSettings.wifiIPMode = readAndWrite("$Sta/IPMode");
        grblSettings.wifiIP = readAndWrite("$Sta/IP");
        grblSettings.apSSID = readAndWrite("$AP/SSID");
        grblSettings.apPassword = readAndWrite("$AP/Password");
        grblSettings.apIP = readAndWrite("$AP/IP");
        grblSettings.apChannel = readAndWrite("$AP/Channel");
        grblSettings.wifiGateway = readAndWrite("$Sta/Gateway");
        grblSettings.wifiNetmask = readAndWrite("$Sta/Netmask");

    changedSettings = grblSettings;

    enableForms();
    updateForms();

}

QString MainWindow::readAndWrite(QString input){

    m_port->write((input + "\r\n").toUtf8());
    m_port->waitForBytesWritten(1000);
    if (waitForReady(m_port, 1000)){
        QString output = m_port->readAll();
        while (waitForReady(m_port, 50)){
            output += m_port->readAll();
        }
        QStringList list = output.split(QRegularExpression("[\r\n]"),Qt::SkipEmptyParts);
        QStringList list2 = list.first().split("=");
       if(!input.contains(list2.first())){
            return readAndWrite(input); //Keep trying.
       }else{
          return list2.last();
       }
    }

    return "";
}

/*
 * Function written by: raimund-schluessler
 * https://github.com/BrillouinMicroscopy/BrillouinAcquisition/pull/135
 */
bool MainWindow::waitForReady(QSerialPort *port, int timeout) {
    port->waitForReadyRead(5);
    QElapsedTimer elapsed;
    elapsed.start();
    while (port->bytesAvailable() == 0 && elapsed.elapsed() < timeout) {
        port->waitForReadyRead(5);
    }
    if (elapsed.elapsed() < timeout) {
        return true;
    }
    return false;
}

void MainWindow::on_connectionButton_clicked()
{
    updateSettings();

    if(m_port->isOpen()){

            if(unsavedNotice("disconnect")){
                ui->connectionButton->setText("Connect");
                m_port->close();

                ui->ipAddressInput->setText("");
                ui->ssidInput->setText("");
                ui->passwordInput->setText("");
                ui->ipGatewayInput->setText("");
                ui->ipNetmaskInput->setText("");

                disableForms();
            }

    }else{

        m_port->open(QIODevice::ReadWrite);

        if(m_port->isOpen()){
            ui->connectionButton->setText("Disconnect");
            refreshSerialData();
            unsavedChanges = false;
        }else{
            QMessageBox msgBox;
            msgBox.setText("Connection failed.");
            msgBox.setInformativeText("Check selected COM port and try again.");
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();
        }
    }
}

void MainWindow::on_updateButton_clicked()
{

    grblSettings.radioMode = readAndWrite("$Radio/Mode=" + changedSettings.radioMode);

    if(changedSettings.radioMode == "STA"){
    grblSettings.wifiSSID = readAndWrite("$Sta/SSID=" + changedSettings.wifiSSID);

    if(grblSettings.apPassword != changedSettings.apPassword)
        readAndWrite("$Sta/Password=" + changedSettings.wifiPassword);

    grblSettings.wifiIPMode = readAndWrite("$Sta/IPMode=" + changedSettings.wifiIPMode);

    if(changedSettings.wifiIPMode == "Static"){
        grblSettings.wifiIP = readAndWrite("$Sta/IP=" + changedSettings.wifiIP);
        grblSettings.wifiGateway = readAndWrite("$Sta/Gateway=" + changedSettings.wifiGateway);
        grblSettings.wifiNetmask = readAndWrite("$Sta/Netmask=" + changedSettings.wifiNetmask);

    }

    }else if(changedSettings.radioMode == "AP"){

        grblSettings.apSSID = readAndWrite("$AP/SSID=" + changedSettings.apSSID);

        if(grblSettings.apPassword != changedSettings.apPassword)
            grblSettings.apPassword = readAndWrite("$AP/Password=" + changedSettings.apPassword);

        grblSettings.apIP = readAndWrite("$AP/IP=" + changedSettings.apIP);
        grblSettings.apChannel = readAndWrite("$AP/Channel=" + changedSettings.apChannel);

    }else{
        //Bluetooth
    }

    grblSettings = changedSettings;
    unsavedChanges = false;
    ui->updateButton->setDisabled(true);

    QMessageBox msgBox;
    msgBox.setText("Settings changed successfully.");
    msgBox.exec();

    refreshSerialData();
    updateForms();

}

void MainWindow::on_Input_changed(){

    if(updateInProgress == false){

        //Save opposite settings first.
        if(ui->wifiModeButton->isChecked() && changedSettings.radioMode == "AP"){
            changedSettings.radioMode = "STA";
            changedSettings.apSSID = ui->ssidInput->text();
            changedSettings.apPassword = ui->passwordInput->text();
            changedSettings.apIP = ui->ipAddressInput->text();
        } else if(ui->apModeButton->isChecked() && changedSettings.radioMode == "STA"){
            changedSettings.radioMode = "AP";
            changedSettings.wifiSSID = ui->ssidInput->text();
            changedSettings.wifiPassword = ui->passwordInput->text();
            changedSettings.wifiIP = ui->ipAddressInput->text();
            changedSettings.wifiGateway = ui->ipGatewayInput->text();
            changedSettings.wifiNetmask = ui->ipNetmaskInput->text();
        } else if(ui->wifiModeButton->isChecked()){
            changedSettings.radioMode = "STA";
            changedSettings.wifiSSID = ui->ssidInput->text();
            changedSettings.wifiPassword = ui->passwordInput->text();
            changedSettings.wifiIP = ui->ipAddressInput->text();
            changedSettings.wifiGateway = ui->ipGatewayInput->text();
            changedSettings.wifiNetmask = ui->ipNetmaskInput->text();
        }else if(ui->apModeButton->isChecked()){
            changedSettings.radioMode = "AP";
            changedSettings.apSSID = ui->ssidInput->text();
            changedSettings.apPassword = ui->passwordInput->text();
            changedSettings.apIP = ui->ipAddressInput->text();
        }else{
            //Bluetooth
        }

        if(ui->dhcpModeButton->isChecked()){
            changedSettings.wifiIPMode = "DHCP";
        }else if(ui->staticModeButton->isChecked()){
            changedSettings.wifiIPMode = "Static";
        }else{
            //Error
        }

        changedSettings.apChannel = ui->apChannelInput->currentText();

    }


    unsavedChanges = true;

    updateForms();
    updateApply();
}


bool MainWindow::unsavedNotice(QString text){
    if(unsavedChanges == false)
        return true;
    QMessageBox msgBox;
    msgBox.setText("You have unsaved changes.");
    msgBox.setInformativeText("Are you sure you want to " + text + "?");
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if(msgBox.exec() == QMessageBox::Yes){
        return true;
    }else{
        return false;
    }
}
