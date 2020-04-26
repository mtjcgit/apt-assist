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

#include <QApplication>

#include "globalvar.h"
#include "mainwindow.h"
#include "dbmanager.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setApplicationName(globalVar::appName());

#ifdef Q_WS_X11
  bool useGUI = getenv("DISPLAY") != 0;
#else
  bool useGUI = true;
#endif

	QApplication app(argc, argv, useGUI);
	globalVar::parseArgs(argc, argv);

#ifdef PREFIX
  QString path = QString(PREFIX);
  if (!path.isEmpty())
    globalVar::setAppPath(path);
#else
  globalVar::setAppPath(app.applicationDirPath());
#endif

	dbmanager::loadAll();

	mainWindow *window = new mainWindow();

 if (useGUI) {
    window->show();
  } else {
    //startConsol();
  }
	return app.exec();
}

