#ifndef threadprocess_H
#define PROCESSMANAGER_H

#include <QThread>
#include <QStringList>

class threadProcess : public QThread
{
Q_OBJECT

public:
  threadProcess(QObject *parent = 0);
  ~threadProcess();
  
public:
  void setProg(const QString &program);
  void setArgs(const QStringList &arguments);
  void setPath(const QString &path);
  void setFile(const QString &file);
  void stop();

protected:
  void run();
  
signals:
  void finished(int exitCode);

private:
  volatile bool stopped;
  QString prog;
  QStringList args;
  QString pth;
  QString fl;
};

#endif

