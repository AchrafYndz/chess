#include "message.h"
#include <QMessageBox>
#include <QString>

void message(const QString &p) {
    QMessageBox box1;
    box1.setText(p);
    box1.exec();
}
