#ifndef BUCLE_H
#define BUCLE_H

#include <QThread>

class bucle : public QThread
{
    Q_OBJECT
public:
    explicit bucle(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // BUCLE_H
