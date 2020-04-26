#####################################################################
# Main project file
#####################################################################

TEMPLATE      = subdirs
CONFIG       += ordered

#process the projects
BUILD_PARTS = app plugins lib doc

for(PROJECT, $$list($$lower($$unique(BUILD_PARTS)))) {
  isEqual(PROJECT, app) {
    SUBDIRS  += src
  #} else:isEqual(PROJECT, plugins) {
  #  SUBDIRS  += plugins
  #} else:isEqual(PROJECT, lib) {
  #  SUBDIRS  += lib
  #} else:isEqual(PROJECT, doc) {
  #  include(doc/doc.pri)
  }
}

### installations ####

data.path     = $${PREFIX}/share/apt-assist
data.files    = share/apt-assist/*
INSTALLS     += data

desktop.path  = $${PREFIX}/share/applications
desktop.files = share/applications/apt-assist.desktop
INSTALLS     += desktop

icons.path  = $${PREFIX}/share/icons
icons.files = share/hicolor
INSTALLS     += icons
