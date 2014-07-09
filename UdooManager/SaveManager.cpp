#include "SaveManager.h"
#include "MainWidget.h"
#include <QSettings>
#include "ui_MainWidget.h"
#include "ChannelEditor.h"
#include <QFile>
#include <QFileInfo>
#include <KF5/KArchive/KZip>
#include <QDebug>
SaveManager::SaveManager(QObject *parent) :
	QObject(parent)
{
}

void SaveManager::save(QString savepath)
{
	QString baseFilename = QFileInfo(savepath).baseName();
	QString iniFullname  = QFileInfo(savepath).path() + "/" + baseFilename + ".ini";
	QString songFullname  = QFileInfo(savepath).path() + "/" + baseFilename + ".song";

	MainWidget* mw = qobject_cast<MainWidget*>(parent());


	//// Écriture du fichier de configuration ////
	QSettings settings(iniFullname, QSettings::IniFormat);
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
						  QFileInfo(mw->channels[i]->getFilename()).fileName());
		settings.setValue(QString("Track%1/boxnumber").arg(i),
						  mw->channels[i]->getBox());
		settings.setValue(QString("Track%1/volume").arg(i), 80);
		settings.setValue(QString("Track%1/pan").arg(i), 0);
	}

	settings.sync();


	//// Archivage ////
	KZip archive(songFullname);
	if (archive.open(QIODevice::WriteOnly))
	{
		archive.addLocalFile(iniFullname, baseFilename + ".ini");

		for(int i = 0; i < mw->channels.size(); ++i)
		{
			archive.addLocalFile(mw->channels[i]->getFilename(),
								 QFileInfo(mw->channels[i]->getFilename()).fileName());
		}

		archive.close();
	}
	else
	{
		qDebug() << "Error.";
	}
}

void SaveManager::load(QString loadpath)
{
	//// Création d'un dossier temporaire ////
	tempdir.reset(new QTemporaryDir);

	//// Extraction de l'archive dans le dossier temp ////
	KZip archive(loadpath);

	if (!archive.open(QIODevice::ReadOnly)) {
		qWarning("Cannot open the archive");
		qWarning("Is it a valid zip file?");
		return;
	}

	const KArchiveDirectory *root = archive.directory();

	root->copyTo(tempdir->path(), true);

	archive.close();

	qDebug() << tempdir->path();

	//// Lecture des données
	// On cherche le .ini :
	QStringList nameFilter("*.ini");
	QDir directory(tempdir->path());
	QString iniFile = tempdir->path() + "/" + directory.entryList(nameFilter).first();
	qDebug() << iniFile;

	MainWidget* mw = qobject_cast<MainWidget*>(parent());
	mw->clearChannels();


	QSettings settings(iniFile, QSettings::IniFormat);

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
