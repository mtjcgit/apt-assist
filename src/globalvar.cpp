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

#include "globalvar.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <QFile>
#include <QDir>
#include <QMessageBox>

QString globalVar::app_path;
QString globalVar::ini_path;

QString globalVar::appName() {
  return "apt-assist";
}

QString globalVar::appVersion() {
  return "0.1.0";
}

QString globalVar::shortDescription()
{
  return "apt assistant";
}

QString globalVar::copyrightStatement()
{
  return "(C) 2009 Mohammad Taqi Jafari";
}

QString globalVar::homepage()
{
  return "http://tuxcom.net";
}

QString globalVar::licenseFile()
{
  QString lf;
  if (QFile::exists( "/usr/share/common-licenses/GPL-3" ) ) {
    lf = "/usr/share/common-licenses/GPL-3";
  } else {
    lf = dataPath() + "/COPYING";
  }
  return lf;
}

QString globalVar::appHomePath() {
#ifndef Q_OS_WIN
  return QDir::homePath() + "/.config/" + appName();
#else
  return QDir::homePath() + "/." + appName();
#endif
}

void globalVar::setAppPath(QString path) {
  app_path = path;
  QDir home;
  if (!home.exists( appHomePath() ) ) {
    home.mkdir ( globalVar::appHomePath() );
  }
  
  if (QFile::exists( dataPath() + "/" + appName() + "rc" )) {
    QFile::copy ( dataPath() + "/" + appName() + "rc", appHomePath() + "/" + appName() + ".ini" );
  }
  /*
   else if (QFile::exists( dataPath() + "/" + appName() + "rc" )) {
    ini_path = dataPath() + "/" + appName() + "rc";
  } 
  */
}

QString globalVar::appPath() {
  return app_path;
}

QString globalVar::libPath() {
  return appPath() + "/lib/" + appName();
}

QString globalVar::dataPath() {
  return appPath() + "/share/" + appName();
}

QString globalVar::defaultLanguage()
{
  return "en";
}

QString globalVar::defaultThemeName() {
  return QLatin1String("oxygen");
}

QString globalVar::defaultIconSize()
{
	return "22";
}

QString globalVar::defaultIcons(QString size, QString cat)
{
	if (size.isEmpty())
		size = defaultIconSize();
	return dataPath() + "/icons/oxygen/" + size + "x" + size + "/" + cat;
}

QString globalVar::tips() {
  return dataPath() + "/tips";
}

QString globalVar::helps() {
  return dataPath() + "/helps";
}

QString globalVar::config() {
  if (QFile::exists( appPath() + "/" + appName() + ".ini" )) {
    ini_path = appPath() + "/" + appName() + ".ini";
  } else {
    ini_path = appHomePath() + "/" + appName() + ".ini";
  }
  /*if (QFile::exists( appHomePath() + "/" + appName() + ".ini" ) ) {
    ini_path = appHomePath() + "/" + appName() + ".ini";
  } else if (QFile::exists( appPath() + "/" + appName() + ".ini" )) {
    ini_path = appPath() + "/" + appName() + ".ini";
  } else {
    //
  }*/
  return ini_path;
}

QString globalVar::translations() {
  return dataPath() + "/translations";
}

QString globalVar::history()
{
  return appHomePath() + "/history";
}

QStringList globalVar::dbs() {
  QStringList plgndir;
  plgndir << globalVar::libPath() + "/dbs" << dataPath() + "/dbs" << appHomePath()  + "/dbs" << "./dbs";
  return plgndir;
}

void globalVar::parseArgs(int argc, char *argv[]) {
  /*some arguments should be processed before others. Handle them now:*/
  for (int i=1; i < argc; i++) {
    //QString s(argv[i]);
    //if (s == "-no-adapt") {
    //}
  }
  
  /*Handle the rest of the arguments. They may override attributes already set:*/
  for (int i=1; i < argc; ++i){
    //QString s(argv[i]);
    QString arg = argv[i];
    if (arg == QLatin1String("-h") || arg == QLatin1String("--help")) {
      
    } else if (arg == QLatin1String("-w") || arg == QLatin1String("--word")) {
      ++i;
      if (i == argc) {
	qWarning("The option -w or --word requires a parameter.");
	return;
      }
      continue;
    }
    /*if (s.startsWith("-h") || s.startsWith("--help")) {
      QMessageBox::warning(0, "Arguments", QString("Usage: " + appName()));
      exit(0);
    } else if (s.startsWith("-w") || s.startsWith("--word")) {
      
    }*/
      
  }
}

