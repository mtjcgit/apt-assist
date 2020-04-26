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

#include <QDir>
#include <QSettings>
#include <QDebug>

#include "dbmanager.h"
#include "globalvar.h"

QStringList dbmanager::osList;
QMultiMap<QString, QString> dbmanager::iconMap, 
			    dbmanager::osMap, 
			    dbmanager::repoMap, 
			    dbmanager::typeMap;
QMultiMap<QString, QStringList> dbmanager::distMap, 
				dbmanager::sectMap, 
				dbmanager::archMap;

void dbmanager::loadDB( const QString &fileName )
{
  QSettings settings(fileName, QSettings::IniFormat);
  QString str0 = settings.value("APTASSIST/Name").toString();

  if( !str0.isEmpty() ) {
    osList.append(str0);
    osMap.insert(str0, settings.value( "APTASSIST/OS" ).toString());
    iconMap.insert(str0, settings.value( "APTASSIST/Icon" ).toString());
    typeMap.insert(str0, settings.value( "APTASSIST/Type" ).toString());
    repoMap.insert(str0, settings.value( "APTASSIST/RepoDir" ).toString());
    distMap.insert(str0, settings.value("APTASSIST/Dists").toString().split(", ", QString::SkipEmptyParts));
    sectMap.insert(str0, settings.value("APTASSIST/Sections").toString().split(", ", QString::SkipEmptyParts));
    archMap.insert(str0, settings.value("APTASSIST/Architecture").toString().split(", ", QString::SkipEmptyParts));
  } else {
    return;
  }
}

void dbmanager::loadAll()
{
  QStringList dirs;
  dirs = globalVar::dbs();

  for (QStringList::const_iterator it = dirs.constBegin(); it != dirs.constEnd(); ++it) {
    QStringList entries = QDir(*it).entryList(QStringList("*.desktop"), QDir::Files );
    for( QStringList::const_iterator it2 = entries.constBegin(); it2 != entries.constEnd(); ++it2 ) {
      loadDB( *it + "/" + *it2 );
    }
  }
}

QStringList dbmanager::foundOSs()
{
  return osList;
}

QString dbmanager::icon(const QString &plgName)
{
  return iconMap.find(plgName).value();
}

QString dbmanager::os(const QString &plgName)
{
  return osMap.find(plgName).value();
}

QString dbmanager::type(const QString &plgName)
{
  return typeMap.find(plgName).value();
}

QString dbmanager::repodir(const QString &plgName)
{
  return repoMap.find(plgName).value();
}

QStringList dbmanager::dists(const QString &plgName)
{
  return distMap.find(plgName).value();
}

QStringList dbmanager::sects(const QString &plgName)
{
  return sectMap.find(plgName).value();
}

QStringList dbmanager::archs(const QString &plgName)
{
  return archMap.find(plgName).value();
}
