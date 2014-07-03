#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

namespace Ui {
	class MainWidget;
}

class ChannelEditor;
class SaveManager;
class MainWidget : public QWidget
{
		Q_OBJECT
		friend class SaveManager;

	public:
		explicit MainWidget(QWidget *parent = 0);
		~MainWidget();

	public slots:
		void changeTrackCount(int);
		void save();
		void load();

	private:
		// Agissent à la fin.
		void addChannel();
		void removeChannel();
		Ui::MainWidget *ui;
		QList<ChannelEditor*> channels;

		SaveManager * savemanager;
};

#endif // MAINWIDGET_H
