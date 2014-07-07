#ifndef CHANNELEDITOR_H
#define CHANNELEDITOR_H

#include <QWidget>

namespace Ui {
	class ChannelEditor;
}

class ChannelEditor : public QWidget
{
		Q_OBJECT

		Q_PROPERTY(QString filename READ getFilename WRITE setFilename)
		Q_PROPERTY(QString name READ getName WRITE setName)
		Q_PROPERTY(int box READ getBox WRITE setBox)
	public:
		explicit ChannelEditor(QWidget *parent = 0);
		~ChannelEditor();

		QString getFilename() const
		{
			return m_filename;
		}

		int getBox() const
		{
			return m_box;
		}

		QString getName() const
		{
			return m_name;
		}

	signals:
		void filenameChanged(QString);
		void boxChanged(int);
		void nameChanged(QString);

	public slots:
		void setFilename(QString arg)
		{
			m_filename = arg;
			emit filenameChanged(m_filename);
		}

		void setBox(int arg)
		{
			m_box = arg;
			emit boxChanged(m_box);
		}

		void setName(QString arg)
		{
			m_name = arg;
			emit nameChanged(m_name);
		}

	private slots:
		void priv_setName(QString arg)
		{
			m_name = arg;
		}

		void priv_setFilename(QString arg)
		{
			m_filename = arg;
		}

		void priv_setBox(int arg)
		{
			m_box = arg;
		}

		void chooseFile();

	private:
		Ui::ChannelEditor *ui;
		QString m_filename{};
		int m_box{};
		QString m_name{};
};

#endif // CHANNELEDITOR_H
