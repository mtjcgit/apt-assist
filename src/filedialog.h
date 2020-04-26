#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QString>
#include <QStringList>
#include <QFileDialog>

class QWidget;

class fileDialog
{
public:
	static QString getOpenFileName( QWidget * parent = 0, 
			const QString & caption = QString(), 
			const QString & dir = QString(), 
			const QString & filter = QString(), 
			QString * selectedFilter = 0, 
			QFileDialog::Options options = QFileDialog::DontResolveSymlinks ) ;

	static QString getExistingDirectory ( QWidget * parent = 0, 
			const QString & caption = QString(), 
			const QString & dir = QString(), 
			QFileDialog::Options options = QFileDialog::ShowDirsOnly );

	static QString getSaveFileName ( QWidget * parent = 0, 
			const QString & caption = QString(), 
			const QString & dir = QString(), 
			const QString & filter = QString(), 
			QString * selectedFilter = 0, 
			QFileDialog::Options options = QFileDialog::DontResolveSymlinks | 
                                           QFileDialog::DontConfirmOverwrite );

	static QStringList getOpenFileNames ( QWidget * parent = 0, 
			const QString & caption = QString(), 
			const QString & dir = QString(), 
			const QString & filter = QString(), 
			QString * selectedFilter = 0, 
			QFileDialog::Options options = QFileDialog::DontResolveSymlinks );

};

#endif
