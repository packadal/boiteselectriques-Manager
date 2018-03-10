#include "ChannelEditor.h"
#include <QFileDialog>
#include "ui_ChannelEditor.h"

ChannelEditor::ChannelEditor(QWidget* parent)
    : QWidget(parent), ui(new Ui::ChannelEditor) {
  ui->setupUi(this);
}

ChannelEditor::~ChannelEditor() {
  delete ui;
}

void ChannelEditor::setBox(int arg) {
  m_box = arg;
  emit boxChanged(m_box);
  ui->box_id->setNum(m_box + 1);
}

void ChannelEditor::chooseFile() {
  QFile f{
      QFileDialog::getOpenFileName(this, "Choisir un fichier audio", QString(),
                                   "Audio file (*.wav *.mp3 *.ogg *.flac)")};
  if (f.exists()) {
    setFilename(f.fileName());  // QFileInfo(f).fileName());
  }
}

void ChannelEditor::chooseImageFile() {
  QFile f{QFileDialog::getOpenFileName(this, "Choisir un fichier audio",
                                       QString(),
                                       "Image file (*.jpeg *.jpg *.png)")};
  if (f.exists()) {
    setImage(f.fileName());  // QFileInfo(f).fileName());
  }
}
