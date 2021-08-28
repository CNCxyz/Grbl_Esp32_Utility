# Grbl_Esp32_Utility (GEU)

![Grbl_Esp32_Utility Screenshot](https://github.com/CNCxyz/Grbl_Esp32_Utility/blob/38bc47e57d0f027121966376c1f70f785fbb909b/GEU-Screenshot.png)

The GEU is a easy to use graphical user interface for [Grbl_Esp32](https://github.com/bdring/Grbl_Esp32). 

The utility allows you to make quick changes to the settings in order to get your Esp32 connected to your network as easily as possible. Once connected to the network, additional settings may be changed through the WebUI.

Current supported settings:

 * Wi-Fi / Access Point Mode
 * SSID & Password
 * Static or DHCP
 * IP Address
 * Access Point Channel
 * Gateway & Netmask

This project is open source and created using the community version of [Qt](https://www.qt.io/download-open-source).

## How to Run

**Windows**

Download the ZIP file and extract the contents to a folder (all files must be present).

Run the EXE file.

**Linux**

Download the Appimage. This image will run on *most* Linux GUI Desktops.

Right click the file and select the permssion: "Allow execution" then double click to run.

*OR*

Open a terminal and run the following command:

    chmod +x Grbl_Esp32_Utility-x86_64.AppImage
    ./Grbl_Esp32_Utility-x86_64.AppImage

**MacOS**

Download the DMG file and double click to run.

If MacOS is not set to run the file immediately, go to "System Preferences > Security & Privacy" then click "Open Anyway".

## How to Compile

Download [Qt for Open Source Development](https://www.qt.io/download-open-source).

Install the latest stable release of Qt 5 or Qt 6 along with the Qt Creator program. Make sure you select "[Serial Port](https://doc.qt.io/qt-5/qtserialport-index.html)" from the additional libraries. 

Download the [Src files](https://github.com/CNCxyz/Grbl_Esp32_Utility/tree/main/src) from the Github repository.

Use the appropriate compiler for Desktop as supplied with the Qt program.

Clean, Build and then Run a "Release" program.

Final versions can be created using:

 * windeployqt.exe (for Windows)
 * macdeployqt.exe (for MacOS)
 * [linuxdeployqt](https://github.com/probonopd/linuxdeployqt) (for Appimages on Linux)

## Developers Wanted!

If you want to help contribute to this project, please do! We are in need of help compiling for additional operating systems, testing and general clean up of code. Open an [Issue](https://github.com/CNCxyz/Grbl_Esp32_Utility/issues) or submit a [Pull Request](https://github.com/CNCxyz/Grbl_Esp32_Utility/pulls).

## License

Grbl_Esp32_Utility (GEU) is licensed under the GPL v3.

    This program is free software: you can redistribute it and/or modify  
    it under the terms of the GNU General Public License as published by  
    the Free Software Foundation, version 3.
    
    This program is distributed in the hope that it will be useful, but 
    WITHOUT ANY WARRANTY; without even the implied warranty of 
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
    General Public License for more details.
    
    You should have received a copy of the GNU General Public License 
    along with this program. If not, see <http://www.gnu.org/licenses/>.
