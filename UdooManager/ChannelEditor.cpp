#include "ChannelEditor.h"
#include "ui_ChannelEditor.h"
#include <QFileDialog>

ChannelEditor::ChannelEditor(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ChannelEditor)
{
	ui->setupUi(this);
}

ChannelEditor::~ChannelEditor()
{
	delete ui;
}

void ChannelEditor::chooseFile()
{
	QFile f{QFileDialog::getOpenFileName(this,
												"Choisir un fichier audio",
												QString(),
												"Audio file (*.wav *.mp3 *.ogg *.flac)")};
	if(f.exists())
	{
		setFilename(f.fileName()); // QFileInfo(f).fileName());
	}
}
