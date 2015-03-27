#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <QObject>
#include <QString>
#include <QDebug>

#include "math.h"

#include "opencv.hpp"

class classifier : public QObject
{
    Q_OBJECT
public:
    explicit classifier(QObject *parent = 0);
    ~classifier();

    void SVMTrain(const cv::Mat &trainData,const cv::Mat &trainLabel,const QString &fileName);
    void SVMParametersSet(const double &gamma, const double &c);
    void SVMLoad(const QString &fileName);
    float SVMPredict(const cv::Mat &testData);


signals:
    void sendMessage(const QString &msg);
public slots:

private:
    //cv::ml::SVM::SVM SVMModel;
    cv::ml::SVM::Params SVMParameters;

    cv::Ptr<cv::ml::SVM> SVMModel;
    cv::Ptr<cv::ml::TrainData> data;
};

#endif // CLASSIFIER_H
