#include "MainWidget.h"
#include "ui_MainWidget.h"

#include "ChannelEditor.h"

#include "SaveManager.h"
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>

MainWidget::MainWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::MainWidget),
	savemanager(new SaveManager(this))
{
	ui->setupUi(this);

	ui->channels->setLayout(new QVBoxLayout);

	// Need to do this because no event loop yet
	addChannel();addChannel();addChannel();addChannel();

	//qobject_cast<QVBoxLayout*>(ui->channels->layout())->insertStretch(-1);
}

MainWidget::~MainWidget()
{
	delete ui;
}

void MainWidget::changeTrackCount(int newCount)
{
	int oldCount = ui->channels->layout()->count();

	if(newCount < oldCount) // Suppression
	{
		/*		int ret = QMessageBox::warning(this, tr("Éditeur de morceaux"),
									   tr("Le nombre de pistes diminue.\n"
										  "Êtes-vous sûr ?"),
									   QMessageBox::Yes | QMessageBox::No,
									   QMessageBox::Yes);

		if(ret == QMessageBox::No)
		{
			ui->trackCount->setValue(oldCount);
			return;
		}
		*/

		for(int i = oldCount; i --> newCount;)
			removeChannel();
	}
	else if(newCount > oldCount) // Ajout
	{
		// Add as many track as needed
		for(int i = oldCount; i < newCount; ++i)
			addChannel();
	}
}

void MainWidget::save()
{
	savemanager->save(QFileDialog::getSaveFileName(this,
												   "Sauvegarder",
												   QString(),
												   "Morceau (*.song)"));
}

void MainWidget::load()
{
	QString file = QFileDialog::getOpenFileName(this,
												"Charger",
												QString(),
												"Morceau (*.song)");
	if(!file.isEmpty())
		savemanager->load(file);
}

void MainWidget::reinit()
{
	clearChannels();

	ui->songName->setText("");
	ui->tempo->setValue(120);
	ui->trackCount->setValue(4);
}

void MainWidget::addChannel()
{
	channels <<  new ChannelEditor(this);

	qobject_cast<QVBoxLayout*>(ui->channels->layout())->addWidget(channels.last());
}

void MainWidget::removeChannel()
{
	auto it = ui->channels->layout()->itemAt(ui->channels->layout()->count() - 1);

	ui->channels->layout()->removeItem(it);
//	ui->channels->layout()->update();

	channels.removeLast();
	delete it->widget();
	delete it;
}

void MainWidget::clearChannels()
{
	ui->trackCount->setValue(0);
}
