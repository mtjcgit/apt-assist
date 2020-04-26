#include "filedialog.h"
//#include <QWidget>

QString fileDialog::getOpenFileName( QWidget * parent, 
			const QString & caption, 
			const QString & dir, const QString & filter, 
			QString * selectedFilter, QFileDialog::Options options ) 
{
	return QFileDialog::getOpenFileName( parent, caption, dir, filter,
										 selectedFilter, options );
}

QString fileDialog::getExistingDirectory ( QWidget * parent, 
			const QString & caption, 
			const QString & dir, 
			QFileDialog::Options options )
{
	return QFileDialog::getExistingDirectory( parent, caption, dir, options );
}

QString fileDialog::getSaveFileName ( QWidget * parent, 
			const QString & caption, 
			const QString & dir, 
			const QString & filter, 
			QString * selectedFilter, 
			QFileDialog::Options options )
{
	return QFileDialog::getSaveFileName( parent, caption, dir, filter,
                                         selectedFilter, options );
}

QStringList fileDialog::getOpenFileNames ( QWidget * parent, 
			const QString & caption, 
			const QString & dir, 
			const QString & filter, 
			QString * selectedFilter, 
			QFileDialog::Options options )
{
	return QFileDialog::getOpenFileNames( parent, caption, dir, filter,
                                          selectedFilter, options );
}

