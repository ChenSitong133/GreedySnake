#include "tools.h"

QString getImagePath(const QString& imageName)
{
    QDir appDir(QCoreApplication::applicationDirPath());
    QString imageDir = QDir(appDir.filePath("..")).filePath("image/"+imageName);
    return imageDir;

}