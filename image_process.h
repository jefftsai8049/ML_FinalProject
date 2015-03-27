#ifndef IMAGE_PROCESS_H
#define IMAGE_PROCESS_H

#include <QObject>

class image_process : public QObject
{
    Q_OBJECT
public:
    explicit image_process(QObject *parent = 0);
    ~image_process();

signals:

public slots:
};

#endif // IMAGE_PROCESS_H
