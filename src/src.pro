#####################################################################
# Application
#####################################################################

TEMPLATE        = app
TARGET          = ../apt-assist
MOC_DIR         = ../build
OBJECTS_DIR     = ../build
DEPENDPATH     += .
INCLUDEPATH    += .

unix {
  # Prefix: base instalation directory
  isEmpty( PREFIX ){
    PREFIX=/usr/local
  }
  message(prefix: $$PREFIX)
  DEFINES += PREFIX=\\\"$${PREFIX}\\\"
}

exists(src/config.h){
  message(found: src/config.h)
  DEFINES += HAVE_CONFIG_H
}

# Input
HEADERS        += globalvar.h                \
									mainwindow.h               \
									dbmanager.h                \
									filechooser.h              \
									filedialog.h               \
									trayicon.h                 \
									threadprocess.h

SOURCES        += main.cpp                   \
									globalvar.cpp              \
									mainwindow.cpp             \
									dbmanager.cpp              \
									filechooser.cpp            \
									filedialog.cpp             \
									trayicon.cpp               \
									threadprocess.cpp

### installations ####

target.path       += $${PREFIX}/bin
INSTALLS          += target

