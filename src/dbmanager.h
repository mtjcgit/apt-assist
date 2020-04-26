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

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QMultiMap>

class dbmanager
{
public:
  static void loadAll();
  static void loadDB( const QString &fileName );

public:
  static QStringList foundOSs();
  static QString icon(const QString &plgName);
  static QString os(const QString &plgName);
  static QString type(const QString &plgName);
  static QString repodir(const QString &plgName);
  static QStringList dists(const QString &plgName);
  static QStringList sects(const QString &plgName);
  static QStringList archs(const QString &plgName);
  /*static QString type(const QString &plgName);
  static bool uid(const QString &plgName);
  static bool gid(const QString &plgName);
*/
private:
  static QStringList osList;
  static QMultiMap<QString, QString> iconMap, osMap, repoMap, typeMap;
  //static QMultiMap<QString, bool> usidMap, gridMap;
  static QMultiMap<QString, QStringList> distMap, sectMap, archMap;
};

#endif

