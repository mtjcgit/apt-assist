#include <QProcess>
#include <QDebug>

#include "threadprocess.h"

threadProcess::threadProcess(QObject *parent) : QThread(parent)
{
  stopped = false;
}

threadProcess::~threadProcess()
{
}

void threadProcess::setProg(const QString &program)
{
  prog = program;
}
void threadProcess::setArgs(const QStringList &arguments)
{
  args = arguments;
}
void threadProcess::setPath(const QString &path)
{
  pth = path;
}
void threadProcess::setFile(const QString &file)
{
  fl = file;
}

void threadProcess::run()
{
  QStringList gzargs;
  QString gzprog = "gzip";
  gzargs.append("-f");
  gzargs.append(fl);

  QProcess *dsproc = new QProcess(this);
  QProcess *gzproc = new QProcess(this);
  dsproc->setStandardOutputProcess(gzproc);
  dsproc->setWorkingDirectory(pth);
  dsproc->setStandardOutputFile(fl, QIODevice::WriteOnly);
  connect(dsproc, SIGNAL(finished(int)), this, SIGNAL(finished(int)));
  
  dsproc->start(prog, args);
  if (dsproc->waitForFinished(-1)) {
     qDebug() << "Make output:" << dsproc->readAll();
  } else {
    qDebug() << "scan failed:" << dsproc->errorString();
    //tray->criticalMessage("scan failed: " + dsproc->errorString());
  }
 
  gzproc->start(gzprog, gzargs);
}

void threadProcess::stop()
{
  stopped = true;
}

