/***************************************************************************
 *   Copyright (C) 2009 by Mohammad Taqi Jafari <mchemtux@gmail.com>       *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA            *
 ***************************************************************************/

#ifndef TRAYICON_H
#define TRAYICON_H

#include <QSystemTrayIcon>
#include <QImage>
#include <QPixmap>

class trayIcon : public QSystemTrayIcon
{
  Q_OBJECT
  
public:
  trayIcon(QWidget *parent = 0);
  ~trayIcon();
  
public:
  void saveSettings();
  void searchMessage(QString msg);
  void simpleMessage(QString msg);
  void informationMessage(QString msg);
  void warningMessage(QString msg);
  void criticalMessage(QString msg);
  /*void showMessagey(const QString &title, const QString &msg, QSystemTrayIcon::MessageIcon icon = Information, int msecs = 10000);*/
  
private:
  void retranslateUi();
  void setupToolTip();
  bool enabledNotify;
  
signals:
  void trayClicked();
  
private slots:
  void trayActivated(QSystemTrayIcon::ActivationReason reason);
  
protected:
  void loadSettings();
  
public:
  QPixmap takeScreenshot() const;
  
};

#endif
