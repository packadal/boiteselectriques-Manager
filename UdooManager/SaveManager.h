#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <QObject>
#include <QTemporaryDir>
#include <memory>

class SaveManager : public QObject
{
		Q_OBJECT
	public:
		explicit SaveManager(QObject *parent = 0);

		std::shared_ptr<QTemporaryDir> tempdir{};

	public slots:
		void save(QString savepath);
		void load(QString name);



};

#endif // SAVEMANAGER_H
