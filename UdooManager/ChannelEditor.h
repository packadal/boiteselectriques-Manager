#ifndef CHANNELEDITOR_H
#define CHANNELEDITOR_H

#include <QWidget>

namespace Ui {
	class ChannelEditor;
}

class ChannelEditor : public QWidget
{
		Q_OBJECT

		Q_PROPERTY(QString name READ getName WRITE setName)
		Q_PROPERTY(int box READ getBox WRITE setBox)
	public:
		explicit ChannelEditor(QWidget *parent = 0);
		~ChannelEditor();

		QString getName() const
		{
			return m_name;
		}

		int getBox() const
		{
			return m_box;
		}

	signals:
		void nameChanged(QString);
		void boxChanged(int);

	public slots:
		void setName(QString arg)
		{
			m_name = arg;
			emit nameChanged(m_name);
		}

		void setBox(int arg)
		{
			m_box = arg;
			emit boxChanged(m_box);
		}

	private slots:
		void priv_setName(QString arg)
		{
			m_name = arg;
		}

		void priv_setBox(int arg)
		{
			m_box = arg;
		}

	private:
		Ui::ChannelEditor *ui;
		QString m_name{};
		int m_box{};
};

#endif // CHANNELEDITOR_H
