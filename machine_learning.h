#ifndef MACHINE_LEARNING_H
#define MACHINE_LEARNING_H



#include <QObject>
#include <QVector>
#include <QStringList>
#include <QString>
#include <QDebug>

#include "opencv.hpp"

class machine_learning : public QObject
{
        Q_OBJECT
public:
    machine_learning(QObject *parent = 0);
    ~machine_learning();

    void openFile(const QStringList &fileNames, QVector<cv::Mat> &src, QVector<float> &srcLabel);
    float extractFileName(const QString &fileName);
    void reshapeCombineImages(const QVector<cv::Mat> &src, cv::Mat &srcSet,const QVector<float> &srcLabel,cv::Mat &trainLabel);
    cv::Mat reshape(const cv::Mat &src);

    void PCA(const cv::Mat &src,cv::Mat &dst);
    void PCAProject(const QString &fileNames,const cv::Mat &src,cv::Mat &dst);
signals:
    void sendMessage(const QString &msg);
};

#endif // MACHINE_LEARNING_H
