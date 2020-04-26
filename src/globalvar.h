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

#ifndef GLOBALVAR_H
#define GLOBALVAR_H

#include <QString>

class globalVar
{
  public:
    static QString appName();
    static QString appVersion();
    static QString shortDescription();
    static QString copyrightStatement();
    static QString homepage();
    static QString licenseFile();
    static void setAppPath(QString path);
    static void parseArgs(int argc, char *argv[]);
    
    static QString appPath();
    static QString libPath();
    static QString dataPath();
    
    //! Return the user's home
    static QString appHomePath();
    
    static QString defaultLanguage();
    static QString defaultThemeName();
    static QString defaultIconSize();
    static QString defaultIcons(QString size, QString cat);
    static QString tips();
    static QString helps();
    static QString config();
    static QString translations();
    static QString history();
    static QStringList dbs();
    
  private:
    static QString app_path;
    static QString ini_path;
};

#endif

