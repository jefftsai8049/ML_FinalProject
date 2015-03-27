#include "classifier.h"

classifier::classifier(QObject *parent) : QObject(parent)
{
    //set SVM type and kernel
    SVMParameters.svmType = cv::ml::SVM::C_SVC;
    SVMParameters.kernelType = cv::ml::SVM::RBF;
    //for RBF
    SVMParameters.gamma = 0.1;
    SVMParameters.C = 1;
}

classifier::~classifier()
{

}

void classifier::SVMTrain(const cv::Mat &trainData, const cv::Mat &trainLabel, const QString &fileName)
{
    //train SVM model
    emit sendMessage("SVM model is training......");
    SVMModel = cv::ml::SVM::create(this->SVMParameters);
    data = cv::ml::TrainData::create(trainData,cv::ml::ROW_SAMPLE,trainLabel);
    SVMModel->train(trainData,cv::ml::ROW_SAMPLE,trainLabel);
    SVMModel->save(fileName.toStdString());
    emit sendMessage("SVM model training is over");
}

void classifier::SVMParametersSet(const double &gamma, const double &c)
{
    //settting RBF kernel parameters
    SVMParameters.gamma = pow(2,gamma);
    SVMParameters.C = pow(2,c);
}

void classifier::SVMLoad(const QString &fileName)
{
    //load SVM model
    SVMModel = cv::ml::StatModel::load<cv::ml::SVM>(fileName.toStdString());
    emit sendMessage("SVM model loaded "+fileName);
}

float classifier::SVMPredict(const cv::Mat &testData)
{
    //predict
    float result = SVMModel->predict(testData);
    return result;
}
