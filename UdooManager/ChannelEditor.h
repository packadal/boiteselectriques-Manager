#ifndef CHANNELEDITOR_H
#define CHANNELEDITOR_H

#include <QWidget>

namespace Ui {
class ChannelEditor;
}

class ChannelEditor : public QWidget {
  Q_OBJECT

  Q_PROPERTY(QString filename READ getFilename WRITE setFilename)
  Q_PROPERTY(QString image READ getImage WRITE setImage)
  Q_PROPERTY(QString name READ getName WRITE setName)
  Q_PROPERTY(int box READ getBox WRITE setBox)
 public:
  explicit ChannelEditor(QWidget* parent = 0);
  ~ChannelEditor();

  QString getFilename() const { return m_filename; }

  QString getImage() const { return m_image; }

  int getBox() const { return m_box; }

  QString getName() const { return m_name; }

 signals:
  void filenameChanged(QString);
  void boxChanged(int);
  void nameChanged(QString);
  void imageChanged(QString);

 public slots:
  void setFilename(QString arg) {
    m_filename = arg;
    emit filenameChanged(m_filename);
  }

  void setBox(int arg);

  void setImage(QString arg) {
    m_image = arg;
    emit imageChanged(m_image);
  }

  void setName(QString arg) {
    m_name = arg;
    emit nameChanged(m_name);
  }

 private slots:
  void priv_setName(QString arg) { m_name = arg; }

  void priv_setFilename(QString arg) { m_filename = arg; }

  void priv_setImageFilename(QString arg) { m_image = arg; }

  void priv_setBox(int arg) { m_box = arg; }

  void chooseFile();

  void chooseImageFile();

 private:
  Ui::ChannelEditor* ui;
  QString m_filename{};
  int m_box{};
  QString m_name{};
  QString m_image{};
};

#endif  // CHANNELEDITOR_H
