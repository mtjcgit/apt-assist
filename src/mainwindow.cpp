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

#include <QtGui>
#include <QFile>
#include <QDebug>
#include <QProcess>

#include "mainwindow.h"
#include "globalvar.h"
#include "filechooser.h"
#include "dbmanager.h"
#include "trayicon.h"

mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent)
{
  centralWidget = new QWidget;
  setCentralWidget(centralWidget);

  optionsGroup = new QGroupBox(this);
  osNameLabel = new QLabel(this);
  distNameLabel = new QLabel(this);
  sectNameLabel = new QLabel(this);
  archNameLabel = new QLabel(this);
  osComboBox = new QComboBox;
  osComboBox->setEditable(true);
  osComboBox->setIconSize(QSize(22, 22));
  connect(osComboBox, SIGNAL(activated(const QString &)), this, SLOT(osComboActivated(const QString &)));
  distComboBox = new QComboBox;
  distComboBox->setEditable(true);
  distComboBox->setIconSize(QSize(22, 22));
  sectComboBox = new QComboBox;
  sectComboBox->setEditable(true);
  sectComboBox->setIconSize(QSize(22, 22));
  archComboBox = new QComboBox;
  archComboBox->setIconSize(QSize(22, 22));
  srcRadioButton = new QRadioButton;
  debRadioButton = new QRadioButton;
  //debRadioButton->setChecked(true);
  /*plRadioButton = new QRadioButton;
  gzRadioButton = new QRadioButton;
  bzRadioButton = new QRadioButton;*/
  udebRadioButton = new QRadioButton;

  repoNameLabel = new QLabel(this);
  repoPath = new fileChooser(this);
  repoPath->setDialogType(fileChooser::GetDirectory);
  scanButton = new QPushButton(this);
  //scanButton->setIconSize(QSize(32, 32));
  connect(scanButton, SIGNAL(clicked()), this, SLOT(startScan()));
  stopButton = new QPushButton(this);
  connect(stopButton, SIGNAL(clicked()), this, SLOT(stopScan()));

  QGridLayout *optionsLayout = new QGridLayout;
  optionsLayout->addWidget(osNameLabel, 0, 0);
  optionsLayout->addWidget(distNameLabel, 0, 1);
  optionsLayout->addWidget(sectNameLabel, 0, 2);
  optionsLayout->addWidget(osComboBox, 1, 0);
  optionsLayout->addWidget(distComboBox, 1, 1);
  optionsLayout->addWidget(sectComboBox, 1, 2);
  optionsLayout->addWidget(archNameLabel, 2, 0);
  optionsLayout->addWidget(archComboBox, 2, 1);
  optionsLayout->addWidget(srcRadioButton, 3, 0);
  optionsLayout->addWidget(debRadioButton, 3, 1);
  optionsLayout->addWidget(udebRadioButton, 3, 2);
  /*optionsLayout->addWidget(plRadioButton, 3, 0);
  optionsLayout->addWidget(gzRadioButton, 3, 1);
  optionsLayout->addWidget(bzRadioButton, 3, 2);*/
  optionsGroup->setLayout(optionsLayout);

  QVBoxLayout *mainLayout = new QVBoxLayout();
  mainLayout->addWidget(optionsGroup);
  mainLayout->addWidget(repoNameLabel);
  mainLayout->addWidget(repoPath);
  mainLayout->addWidget(scanButton);
  mainLayout->addWidget(stopButton);
  mainLayout->addStretch(0);
  centralWidget->setLayout(mainLayout);

  createActions();
  createMenus();
  createToolbars();
  retranslateUi();
  createOSList();
  createTrayIcon();

  connect(tray, SIGNAL(trayClicked()), this, SLOT(toggleWindow()));
  connect(trayAction, SIGNAL(triggered(bool)), tray, SLOT(setVisible(bool)));

  //cursor = new QCursor(Qt::ArrowCursor);
}

mainWindow::~mainWindow()
{
  //saveSettings();
}

void mainWindow::onWhatsThis()
{
  QWhatsThis::enterWhatsThisMode();
}

void mainWindow::createActions()
{
quitAction = new QAction(this);
  connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
  settingsAction = new QAction(this);
  //connect(settingsAction, SIGNAL(triggered()), this, SLOT(showSettingsDialog()));
  tipAction = new QAction(this);
  //connect(tipAction, SIGNAL(triggered()), this, SLOT(showTipDialog()));
  helpAction = new QAction(this);
  //connect(helpAction, SIGNAL(triggered()), this, SLOT(showHelpDialog()));
  languageAction = new QAction(this);
  //connect(languageAction, SIGNAL(triggered()), this, SLOT(showLanguageDialog()));
  whatsThisAction = new QAction(this);
  //connect(whatsThisAction, SIGNAL(triggered()), this, SLOT(onWhatsThis()));
  aboutAction = new QAction(this);
  //connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAboutDialog()));
  aboutQtAction = new QAction(this);
  connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
  scanAction = new QAction(this);
  connect(scanAction, SIGNAL(triggered()), this, SLOT(startScan()));
  trayAction = new QAction(this);
  trayAction->setCheckable(true);
}

void mainWindow::createMenus()
{
  fileMenu = new QMenu(this);
  fileMenu->addSeparator();
  fileMenu->addAction(quitAction);
  editMenu = new QMenu(this);
  viewMenu = new QMenu(this);
  viewMenu->addAction(trayAction);
  toolMenu = new QMenu(this);
  toolMenu->addAction(scanAction);
  settingMenu = new QMenu(this);
  settingMenu->addAction(settingsAction);
  helpMenu = new QMenu(this);
  helpMenu->addAction(helpAction);
  helpMenu->addAction(whatsThisAction);
  helpMenu->addSeparator();
  helpMenu->addAction(tipAction);
  helpMenu->addSeparator();
  helpMenu->addAction(languageAction);
  helpMenu->addSeparator();
  helpMenu->addAction(aboutAction);
  helpMenu->addSeparator();
  helpMenu->addAction(aboutQtAction);

  menuBar()->addMenu(fileMenu);
  menuBar()->addMenu(editMenu);
  menuBar()->addMenu(viewMenu);
  menuBar()->addMenu(toolMenu);
  menuBar()->addMenu(settingMenu);
  menuBar()->addSeparator();
  menuBar()->addMenu(helpMenu);
}

void mainWindow::createToolbars()
{
  mainToolBar = new QToolBar(this);
  mainToolBar->addAction(settingsAction);
  mainToolBar->addSeparator();
  mainToolBar->addAction(aboutAction);
  mainToolBar->addSeparator();
  //mainToolBar->addSeparator();
  mainToolBar->addAction(quitAction);

  addToolBar(mainToolBar);
}

void mainWindow::createTrayIcon()
{
  trayIconMenu = new QMenu(this);
  trayIconMenu->addAction(scanAction);
  trayIconMenu->addSeparator();
  trayIconMenu->addAction(quitAction);

  tray = new trayIcon(this);
  tray->setContextMenu(trayIconMenu);
}

void mainWindow::toggleWindow()
{
  //this->setVisible(!this->isVisible());
  setVisible(!isVisible());
}

void mainWindow::retranslateUi()
{
  fileMenu->setTitle(tr("&File"));
  editMenu->setTitle(tr("&Edit"));
  viewMenu->setTitle(tr("&View"));
  toolMenu->setTitle(tr("&Tools"));
  settingMenu->setTitle(tr("&Settings"));
  helpMenu->setTitle(tr("&Help"));

  quitAction->setText(tr("&Quit"));
  quitAction->setShortcut(tr("Ctrl+Q"));
  quitAction->setStatusTip(tr("Quit %1").arg(globalVar::appName()));
  quitAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/application-exit.png"));

  settingsAction->setText(tr("&Settings"));
  settingsAction->setShortcut(tr("Ctrl+S"));
  settingsAction->setStatusTip(tr("Configure %1").arg(globalVar::appName()));
  settingsAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/configure.png"));

  whatsThisAction->setText(tr("&What's This?"));
  whatsThisAction->setShortcut(tr("Shift+F1"));
  whatsThisAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/help-contextual.png"));

  helpAction->setText(tr("Help %1").arg(globalVar::appName()));
  helpAction->setShortcut(tr("F1"));
  helpAction->setStatusTip(tr("Help %1").arg(globalVar::appName()));
  helpAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/help-contents.png"));

  tipAction->setText(tr("&Tip of the Day"));
  tipAction->setShortcut(tr("Ctrl+T"));
  tipAction->setStatusTip(tr("tip of the day"));
  tipAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/tip.png"));

  languageAction->setText(tr("Switch Application &Language..."));
  languageAction->setShortcut(tr("Ctrl+L"));
  languageAction->setStatusTip(tr("change %1 language").arg(globalVar::appName()));
  languageAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/change-language.png"));

  aboutAction->setText(tr("A&bout"));
  aboutAction->setShortcut(tr("Ctrl+B"));
  aboutAction->setStatusTip(tr("About %1").arg(globalVar::appName()));
  aboutAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/help-about.png"));

  aboutQtAction->setText(tr("About &Qt"));
  aboutQtAction->setShortcut(tr("Ctrl+Q"));
  aboutQtAction->setStatusTip(tr("About Qt"));
  aboutQtAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/help-about-qt.png"));

  scanAction->setText(tr("Start &Scan"));
  scanAction->setStatusTip(tr("Start rescan..."));
  scanAction->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/system-search.png"));

  trayAction->setText(tr("Show system &tray icon"));
  //trayAction->setShortcut(tr("Ctrl+T"));
  trayAction->setStatusTip(tr("Show %1 icon in system tray").arg(globalVar::appName()));

  optionsGroup->setTitle("&Options...");
  osNameLabel->setText(tr("Operating System:"));
  distNameLabel->setText(tr("Distribution:"));
  sectNameLabel->setText(tr("Section:"));
  archNameLabel->setText(tr("Architecture:"));
  srcRadioButton->setText(tr("Source"));
  debRadioButton->setText(tr("Binary"));
  udebRadioButton->setText(tr("debian Installer"));

  /*plRadioButton->setText(tr("Plain"));
  gzRadioButton->setText(tr("Gzip"));
  bzRadioButton->setText(tr("Bzip"));*/

  repoNameLabel->setText(tr("Repository:"));
  repoPath->setCaption(tr("Select Repository directory."));
  scanButton->setText("&Scan");
  scanButton->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/system-search.png"));
  stopButton->setText("&Stop");
  stopButton->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/system-search.png"));
}

void mainWindow::createOSList()
{
  foreach (QString item, dbmanager::foundOSs()) {
    osComboBox->addItem(QIcon(globalVar::defaultIcons("22", "os") + "/" + dbmanager::icon(item)), item);
  }
}

void mainWindow::osComboActivated(QString value)
{
  distComboBox->clear();
  distComboBox->addItems(dbmanager::dists(value));

  sectComboBox->clear();
  sectComboBox->addItems(dbmanager::sects(value));

  archComboBox->clear();
  archComboBox->addItems(dbmanager::archs(value));
  //FIXME select current machine architecture by dpkg-architecture

  if (dbmanager::type(value) == "source")
    srcRadioButton->setChecked(true);
  else if (dbmanager::type(value) == "binary")
    debRadioButton->setChecked(true);
  else  if (dbmanager::type(value) == "installer")
    udebRadioButton->setChecked(true);

  repoPath->setText(dbmanager::repodir(value));
}

void mainWindow::startScan()
{
  scanButton->setEnabled(false);
  QString dsprog, outfile;
  QStringList dsargs, gzargs;

  if (srcRadioButton->isChecked()) {
    dsprog = "dpkg-scansources";
    outfile = "/source/Sources";
  } else if (debRadioButton->isChecked()) {
    dsprog = "dpkg-scanpackages";
    outfile = "/binary-" + archComboBox->currentText() + "/Packages";
    dsargs.append("--arch");
    dsargs.append(archComboBox->currentText());
  } else if (udebRadioButton->isChecked()) {
    dsprog = "dpkg-scanpackages";
    outfile = "/debian-installer/binary-" + archComboBox->currentText() + "/Packages";
    dsargs.append("--udeb");
    dsargs.append("--arch");
    dsargs.append(archComboBox->currentText());
  }
  
  QString destFile = repoPath->text() + "/dists/" + distComboBox->currentText() + "/" + sectComboBox->currentText() + outfile;
  
  dsargs.append("pool/" + sectComboBox->currentText());
  /*QString gzprog = "gzip";
  gzargs.append("-f");
  gzargs.append(destFile);

  QProcess *dsproc = new QProcess(this);
  QProcess *gzproc = new QProcess(this);
  dsproc->setStandardOutputProcess(gzproc);
  dsproc->setWorkingDirectory(repoPath->text());
  dsproc->setStandardOutputFile(destFile, QIODevice::WriteOnly);

  connect(dsproc, SIGNAL(started()), this, SLOT(wait()));
  connect(dsproc, SIGNAL(finished(int)), this, SLOT(finished(int)));

  dsproc->start(dsprog, dsargs);

  if (dsproc->waitForFinished(-1)) {
     qDebug() << "Make output:" << dsproc->readAll();
  } else {
    tray->criticalMessage("scan failed: " + dsproc->errorString());
  }
 
  gzproc->start(gzprog, gzargs);*/
  thrdPrs = new threadProcess(this);
  thrdPrs->setProg(dsprog);
  thrdPrs->setArgs(dsargs);
  thrdPrs->setPath(repoPath->text());
  thrdPrs->setFile(destFile);
  //thrdPrs->run(dsprog, dsargs, repoPath->text(), destFile);
  thrdPrs->start();
  connect(thrdPrs, SIGNAL(finished(int)), this, SLOT(finished(int)));
}

void mainWindow::stopScan()
{
  if (thrdPrs)
    thrdPrs->stop();
}

void mainWindow::closeEvent(QCloseEvent *event)
{
  thrdPrs->stop();
  thrdPrs->wait();
  event->accept();
}

void mainWindow::wait()
{
  //cursor->setShape(Qt::BusyCursor);
//qDebug() << "started:";
}

void mainWindow::finished(int exitCode)
{
  scanButton->setEnabled(true);
  //cursor->setShape(Qt::ArrowCursor);
  tray->informationMessage("scan finished.");
}
