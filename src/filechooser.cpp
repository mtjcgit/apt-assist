#include <QtGui>

#include "filechooser.h"
#include "filedialog.h"
#include "globalvar.h"

fileChooser::fileChooser(QWidget *parent) : QWidget(parent)
{
	line_edit = new QLineEdit(this);
	clear = new QToolButton(this);
	clear->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/edit-clear-locationbar-ltr.png"));
	connect(clear, SIGNAL(clicked()), line_edit, SLOT(clear()));
	button = new QToolButton(this);
	button->setIcon(QIcon(globalVar::defaultIcons("22", "actions") + "/document-open-folder.png"));
	connect(button, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
	connect(line_edit, SIGNAL(editingFinished()), this, SLOT(lineditState()));
	connect(line_edit, SIGNAL(textChanged(const QString&)), this, SIGNAL(textChanged(const QString&)));
	connect(line_edit, SIGNAL(textEdited(const QString&)), this, SIGNAL(textEdited(const QString&)));
	connect(line_edit, SIGNAL(textEdited(const QString&)), this, SLOT(checkPrefix(const QString&)));
	
	QHBoxLayout *margin = new QHBoxLayout();
	margin->addWidget(clear);
	margin->addWidget(line_edit);
	margin->addWidget(button);
	margin->setSpacing(0);
	
	//margin->addStretch(1);
	//margin->addSpacing(1);
	setLayout(margin);
	
	setDialogType(GetFileName);
	setOptions(0);
	line_edit->setFocus();
}

fileChooser::~fileChooser()
{
}

QString fileChooser::text() const
{
	return line_edit->text();
}

bool fileChooser::modification() const
{
	return line_edit->isModified();
}

void fileChooser::setText(const QString & text) {
	line_edit->setText(text);
}

void fileChooser::on_button_clicked() {
	QString result;
	QString f;

	if (dialogType() == GetFileName) {
		QFileDialog::Options opts = options();
		if (opts == 0) opts = QFileDialog::DontResolveSymlinks;

		result = fileDialog::getOpenFileName( 
                        this, caption(),
                        line_edit->text(),
                        filter(), &f, opts );
	}
	else
	if (dialogType() == GetDirectory) {
		QFileDialog::Options opts = options();
		if (opts == 0) opts = QFileDialog::ShowDirsOnly;

		result = fileDialog::getExistingDirectory(
                    this, caption(),
                    line_edit->text(), opts );
	}

	if (!result.isEmpty()) {
		line_edit->setText(result);
		line_edit->setModified(1);
		emit lineditChanged(modification());
	}
}

void fileChooser::lineditState()
{
	emit lineditChanged(modification());
}

void fileChooser::checkPrefix(const QString &url)
{
  if (url.startsWith(QLatin1String("file://"))) {
    line_edit->setText(url.toLatin1().mid(7));
  }
}
