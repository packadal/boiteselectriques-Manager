#include "SaveManager.h"
#include "MainWidget.h"
#include <QSettings>
#include "ui_MainWidget.h"
#include "ChannelEditor.h"

#include <qdebug.h>
SaveManager::SaveManager(QObject *parent) :
	QObject(parent)
{
}

void SaveManager::save(QString name)
{
	MainWidget* mw = qobject_cast<MainWidget*>(parent());

	QSettings settings(name, QSettings::IniFormat);

	settings.setValue("general/songName",
					  mw->ui->songName->text());
	settings.setValue("general/tempo",
					  mw->ui->tempo->value());
	settings.setValue("general/trackCount",
					  mw->ui->trackCount->value());

	qDebug() << mw->channels.size();

	for(int i = 0; i < mw->channels.size(); ++i)
	{
		qDebug()<<"blop";
		settings.setValue(QString("track%1/filename").arg(i),
						  mw->channels[i]->getName());
		settings.setValue(QString("track%1/boxnumber").arg(i),
						  mw->channels[i]->getBox());
	}

}

void SaveManager::load(QString name)
{
	MainWidget* mw = qobject_cast<MainWidget*>(parent());

	QSettings settings(name, QSettings::IniFormat);
}
