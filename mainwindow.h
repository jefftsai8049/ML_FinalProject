#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QStringList>
#include <QString>
#include <QDebug>
#include <QVector>
#include <QFile>
#include <QTime>

#include "classifier.h"
#include "image_process.h"
#include "machine_learning.h"
#include "image_process.h"
#include "opencv.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_openFiles_pushButton_clicked();

    void on_imageProcess_pushButton_clicked();

    void on_machineLearning_pushButton_clicked();

    void on_trainClassifier_pushButton_clicked();

    void receiveMessage(const QString &msg);

    void on_SVM_gamma_doubleSpinBox_editingFinished();

    void on_loadSVM_pushButton_clicked();

    void on_accuracy_pushButton_clicked();

    void on_SVM_gamma_doubleSpinBox_valueChanged(double arg1);

    void on_SVM_c_doubleSpinBox_valueChanged(double arg1);

    void on_gridTrainClassifier_pushButton_clicked();

    void on_gridTest_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QFileDialog *fileDialog;
    machine_learning *ML;
    image_process *IP;
    classifier *CF;

    QVector<cv::Mat> srcRaw;
    QVector<float> srcLabel;
    QVector<cv::Mat> srcRawTest;
    QVector<float> srcLabelTest;

    cv::Mat trainData;
    cv::Mat trainLabel;
    cv::Mat testData;
    cv::Mat testLabel;
};

#endif // MAINWINDOW_H
