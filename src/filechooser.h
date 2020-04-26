#ifndef FILECHOOSER_H
#define FILECHOOSER_H

#include <QFileDialog>

class QLineEdit;
class QToolButton;

class fileChooser : public QWidget
{
Q_OBJECT
Q_PROPERTY(QString text READ text WRITE setText)
Q_PROPERTY(QString caption READ caption WRITE setCaption)
Q_PROPERTY(QString filter READ filter WRITE setFilter)
Q_PROPERTY(DialogType dialogType READ dialogType WRITE setDialogType)
Q_PROPERTY(QFileDialog::Options options READ options WRITE setOptions)

public:
	enum DialogType { GetFileName = 0, GetDirectory = 1 };
	
	fileChooser( QWidget* parent = 0 );
	~fileChooser();

public:
	QString text() const;
	QString caption() const { return _caption; };
	QString filter() const { return _filter; };
	DialogType dialogType() const { return _type; };
	QFileDialog::Options options() const { return _options; };
	bool modification() const;
	
signals:
	bool lineditChanged(bool);
	QString textChanged(const QString&);
	QString textEdited(const QString&);

public slots:
	void setText(const QString & text);
	void setCaption(const QString & caption) { _caption = caption; };
	void setFilter(const QString & filter) { _filter = filter; };
	void setDialogType( DialogType type) { _type = type; };
	void setOptions( QFileDialog::Options options) { _options = options; };

private slots:
	void checkPrefix(const QString &url);
	
protected:
	QString _caption;
	QString _filter;
	DialogType _type;
	QFileDialog::Options _options;

protected slots:
	virtual void on_button_clicked();
	virtual void lineditState();

private:
	QLineEdit *line_edit;
	QToolButton *button;
	QToolButton *clear;
};

#endif
