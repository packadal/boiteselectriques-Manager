#include "ChannelEditor.h"
#include "ui_ChannelEditor.h"

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
