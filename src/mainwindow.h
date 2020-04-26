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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "threadprocess.h"

class QGroupBox;
class QAction;
class QMenu;
class QToolBar;
class QLabel;
class QComboBox;
class QRadioButton;
class QPushButton;
//class QProgressDialog;
class QProcess;
//class QCursor;
class fileChooser;
class trayIcon;

class mainWindow : public QMainWindow
{
Q_OBJECT
  
public:
  mainWindow(QWidget *parent = 0);
  ~mainWindow();

private:
  void createActions();
  void createMenus();
  void createToolbars();
  void retranslateUi();
  void createOSList();
  void createTrayIcon();

private slots:
  void onWhatsThis();
  void osComboActivated(QString value);
  void toggleWindow();
  void startScan();
  void stopScan();

protected slots:
  //void scan();
  void wait();
  void finished(int exitCode);

protected:
  void closeEvent(QCloseEvent *event);

private:
  QWidget *centralWidget;
  QAction *quitAction;
  QAction *settingsAction;
  QAction *whatsThisAction;
  QAction *helpAction;
  QAction *tipAction;
  QAction *languageAction;
  QAction *aboutAction;
  QAction *aboutQtAction;
  QAction *scanAction;
  QAction *trayAction;
  QMenu *fileMenu;
  QMenu *editMenu;
  QMenu *viewMenu;
  QMenu *toolMenu;
  QMenu *settingMenu;
  QMenu *helpMenu;
  QMenu *trayIconMenu;
  QToolBar *mainToolBar;
  QGroupBox *optionsGroup;
  QLabel *osNameLabel;
  QLabel *distNameLabel;
  QLabel *sectNameLabel;
  QLabel *repoNameLabel;
  QLabel *archNameLabel;
  QComboBox *osComboBox;
  QComboBox *distComboBox;
  QComboBox *sectComboBox;
  QComboBox *archComboBox;
  QRadioButton *srcRadioButton;
  QRadioButton *debRadioButton;
  QRadioButton *udebRadioButton;
  /*QRadioButton *plRadioButton;
  QRadioButton *gzRadioButton;
  QRadioButton *bzRadioButton;*/
  QPushButton *scanButton;
  QPushButton *stopButton;
  //QProgressDialog *progressDlg;
  QProcess *dsproc;
  QProcess *gzproc;
  //QCursor *cursor;
  fileChooser *repoPath;
  trayIcon *tray;
  threadProcess *thrdPrs;
};

#endif

