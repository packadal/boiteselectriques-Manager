#include "SaveManager.h"
#include "MainWidget.h"
#include <QSettings>
#include "ui_MainWidget.h"
#include "ChannelEditor.h"

SaveManager::SaveManager(QObject *parent) :
	QObject(parent)
{
}

void SaveManager::save(QString name)
{
	MainWidget* mw = qobject_cast<MainWidget*>(parent());

	QSettings settings(name, QSettings::IniFormat);
	settings.clear();

	settings.setValue("General/songName",
					  mw->ui->songName->text());
	settings.setValue("General/tempo",
					  mw->ui->tempo->value());
	settings.setValue("General/trackCount",
					  mw->ui->trackCount->value());

	for(int i = 0; i < mw->channels.size(); ++i)
	{
		settings.setValue(QString("Track%1/name").arg(i),
						  mw->channels[i]->getName());
		settings.setValue(QString("Track%1/filename").arg(i),
						  mw->channels[i]->getFilename());
		settings.setValue(QString("Track%1/boxnumber").arg(i),
						  mw->channels[i]->getBox());
		settings.setValue(QString("Track%1/volume").arg(i), 80);
		settings.setValue(QString("Track%1/pan").arg(i), 0);
	}
}

void SaveManager::load(QString name)
{
	MainWidget* mw = qobject_cast<MainWidget*>(parent());
	mw->clearChannels();


	QSettings settings(name, QSettings::IniFormat);

	mw->ui->songName->setText(settings.value("General/songName").toString());
	mw->ui->tempo->setValue(settings.value("General/tempo").toInt());
	mw->ui->trackCount->setValue(settings.value("General/trackCount").toInt());

	int n = mw->ui->trackCount->value();
	for(int i = 0; i < n; ++i)
	{
		mw->channels[i]->setName(settings.value(QString("Track%1/name").arg(i)).toString());
		mw->channels[i]->setFilename(settings.value(QString("Track%1/filename").arg(i)).toString());
		mw->channels[i]->setBox(settings.value(QString("Track%1/boxnumber").arg(i)).toInt());
	}

}
