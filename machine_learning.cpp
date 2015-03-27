#include "machine_learning.h"

machine_learning::machine_learning(QObject *parent)
{

}

machine_learning::~machine_learning()
{

}

void machine_learning::openFile(const QStringList &fileNames,QVector<cv::Mat> &src,QVector<float> &srcLabel)
{
    for(int i=0;i<fileNames.size();i++)
    {
        //read image file
        cv::Mat temp;
        cv::cvtColor(cv::imread(fileNames[i].toStdString()),temp,cv::COLOR_BGR2GRAY);
        src.push_back(temp);

        //read filenames to get label
        srcLabel.push_back(this->extractFileName(fileNames[i]));
    }
    emit sendMessage("Files opened");
}

float machine_learning::extractFileName(const QString &fileName)
{
    //get label from filename
    if(fileName.indexOf("_A.") != -1)
        return 1;
    if(fileName.indexOf("_B.") != -1)
        return 2;
    if(fileName.indexOf("_C.") != -1)
        return 3;
    if(fileName.indexOf("_D.") != -1)
        return 4;
    if(fileName.indexOf("_E.") != -1)
        return 5;
    if(fileName.indexOf("_F.") != -1)
        return 6;
    if(fileName.indexOf("_G.") != -1)
        return 7;
    if(fileName.indexOf("_H.") != -1)
        return 8;
    if(fileName.indexOf("_I.") != -1)
        return 9;
    if(fileName.indexOf("_J.") != -1)
        return 10;
    if(fileName.indexOf("_K.") != -1)
        return 11;
    if(fileName.indexOf("_L.") != -1)
        return 12;
    if(fileName.indexOf("_M.") != -1)
        return 13;
    if(fileName.indexOf("_N.") != -1)
        return 14;
    if(fileName.indexOf("_O.") != -1)
        return 15;
    if(fileName.indexOf("_P.") != -1)
        return 16;
    if(fileName.indexOf("_R.") != -1)
        return 17;
    if(fileName.indexOf("_S.") != -1)
        return 18;
    if(fileName.indexOf("_T.") != -1)
        return 19;
    if(fileName.indexOf("_U.") != -1)
        return 20;
    if(fileName.indexOf("_V.") != -1)
        return 21;
    if(fileName.indexOf("_W.") != -1)
        return 22;
    if(fileName.indexOf("_X.") != -1)
        return 23;
    if(fileName.indexOf("_Y.") != -1)
        return 24;
    if(fileName.indexOf("_Z.") != -1)
        return 25;
    else
        return 0;
}

void machine_learning::reshapeCombineImages(const QVector<cv::Mat> &src, cv::Mat &srcSet, const QVector<float> &srcLabel, cv::Mat &trainLabel)
{
    //reshape 2D matrix to 1D vector and combine data vectors together
    for(int i=0;i<src.size();i++)
    {
        cv::Mat temp;


        temp = src[i].reshape(1,1);
        cv::normalize(temp,temp,0,1,cv::NORM_MINMAX);
        temp.convertTo(temp,CV_32FC1);
        srcSet.push_back(temp);
    }


    trainLabel = cv::Mat(srcLabel.toStdVector());
    trainLabel.convertTo(trainLabel,CV_32SC1);
}

cv::Mat machine_learning::reshape(const cv::Mat &src)
{
    //only reshape 2D matrix to 1D vector
    cv::Mat temp;
    temp = src.reshape(1,1);
    cv::normalize(temp,temp,0,1,cv::NORM_MINMAX);
    temp.convertTo(temp,CV_32FC1);
    emit sendMessage("Resahpe datas");
    return temp;
}

void machine_learning::PCA(const cv::Mat &src, cv::Mat &dst)
{
    //PCA and save matrix
    cv::PCA pca(src,cv::Mat(),cv::PCA::DATA_AS_ROW,25);
    cv::Mat project = pca.project(src);

    if(dst.type() != CV_32FC1)
        dst.convertTo(dst,CV_32FC1);
    dst = project.clone();
    cv::imshow("pcadst",dst);
    cv::normalize(dst,dst,0,1,cv::NORM_MINMAX);
    cv::FileStorage PCA_save("PCA_Model.txt",cv::FileStorage::WRITE);
    pca.write(PCA_save);
}

void machine_learning::PCAProject(const QString &fileNames, const cv::Mat &src, cv::Mat &dst)
{
    //read PCA matrix from model and project original matrix to PC
    cv::PCA pca;
    cv::FileStorage PCA_read(fileNames.toStdString(),cv::FileStorage::READ);
    PCA_read["mean"] >> pca.mean;
    PCA_read["vectors"] >> pca.eigenvectors;
    PCA_read["values"] >> pca.eigenvalues;
    if(dst.type() != CV_32FC1)
        dst.convertTo(dst,CV_32FC1);
    dst = pca.project(src);
    cv::normalize(dst,dst,0,1,cv::NORM_MINMAX);

}

