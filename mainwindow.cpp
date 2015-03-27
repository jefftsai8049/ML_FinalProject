#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fileDialog = new QFileDialog;
    ML = new machine_learning;
    IP = new image_process;
    CF = new classifier;

    connect(CF,SIGNAL(sendMessage(QString)),this,SLOT(receiveMessage(QString)));
    connect(ML,SIGNAL(sendMessage(QString)),this,SLOT(receiveMessage(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ML;
    delete IP;
}

void MainWindow::on_openFiles_pushButton_clicked()
{
    //open trai file
    QStringList fileNames = fileDialog->getOpenFileNames(this, tr("Open image File"), ".", tr("Image Files(*.jpg)"));
    if(fileNames.isEmpty())
        return;
    ML->openFile(fileNames,srcRaw,srcLabel);

    ui->statusBar->showMessage("Opened "+QString::number(fileNames.size())+" files.");
}

void MainWindow::on_imageProcess_pushButton_clicked()
{

}

void MainWindow::on_machineLearning_pushButton_clicked()
{
    //reshape and PCA
    ML->reshapeCombineImages(srcRaw,trainData,srcLabel,trainLabel);
    cv::imshow("trainData",trainData);
    cv::Mat dst;
    if(ui->PCA_checkBox->isChecked())
    {
        ML->PCA(trainData,dst);
    }
    else
    {
        dst = trainData.clone();
    }



    this->trainData = dst.clone();
    cv::imshow("this->trainData.row(0)",this->trainData.row(0));


}

void MainWindow::on_trainClassifier_pushButton_clicked()
{
    //train single model
    QString gamma = QString::number(ui->SVM_gamma_doubleSpinBox->value());
    QString c = QString::number(ui->SVM_c_doubleSpinBox->value());
    CF->SVMTrain(this->trainData,this->trainLabel,"SVM_C="+c+"_gamma="+gamma+"_model.xml");
}

void MainWindow::receiveMessage(const QString &msg)
{
    ui->textBrowser->setPlainText(msg);
}

void MainWindow::on_SVM_gamma_doubleSpinBox_editingFinished()
{

}

void MainWindow::on_loadSVM_pushButton_clicked()
{
    //load SVM model
    QString fileName = fileDialog->getOpenFileName(this, tr("Open Model File"), ".", tr("Model Files(*.xml)"));
    if(fileName.isEmpty())
        return;
    CF->SVMLoad(fileName);
}

void MainWindow::on_accuracy_pushButton_clicked()
{
    //for test single model
    QStringList fileNames = fileDialog->getOpenFileNames(this, tr("Open image File"), ".", tr("Image Files(*.jpg)"));
    if(fileNames.isEmpty())
        return;
    ML->openFile(fileNames,srcRawTest,srcLabelTest);

    ui->statusBar->showMessage("Opened test data "+QString::number(fileNames.size())+" files.");

    ML->reshapeCombineImages(srcRawTest,testData,srcLabelTest,testLabel);

    cv::Mat PCATestData;
    if(ui->PCA_checkBox->isChecked())
    {
        ML->PCAProject("PCA_Model.txt",testData,PCATestData);
    }
    else
    {
        PCATestData = testData.clone();
    }

    float accurary = 0;
    QVector<float> predictLabelTest;
    for(int i=0;i<fileNames.size();i++)
    {
        predictLabelTest.push_back(CF->SVMPredict(PCATestData));
        if(srcLabelTest[i] - predictLabelTest[i] < 0.5)
            accurary++;
    }
}

void MainWindow::on_SVM_gamma_doubleSpinBox_valueChanged(double arg1)
{
    CF->SVMParametersSet(ui->SVM_gamma_doubleSpinBox->value(),ui->SVM_c_doubleSpinBox->value());
}

void MainWindow::on_SVM_c_doubleSpinBox_valueChanged(double arg1)
{
    CF->SVMParametersSet(ui->SVM_gamma_doubleSpinBox->value(),ui->SVM_c_doubleSpinBox->value());
}

void MainWindow::on_gridTrainClassifier_pushButton_clicked()
{
    //for RBF
    int C_lower = -5;
    int C_upper = 15;
    int Gamma_lower = -15;
    int Gamma_upper = 3;
    for(int i=0;i<(C_upper-C_lower);i++)
    {
        for(int j=0;j<(Gamma_upper-Gamma_lower);j++)
        {
            CF->SVMParametersSet(j+Gamma_lower,i+C_lower);
            ui->statusBar->showMessage("SVM model is training......"+("SVM_C="+QString::number(i+C_lower)+"_gamma="+QString::number(j+Gamma_lower)+"_model.xml"));
            CF->SVMTrain(this->trainData,this->trainLabel,"SVM_C="+QString::number(i+C_lower)+"_gamma="+QString::number(j+Gamma_lower)+"_PCA_model.xml");
            ui->statusBar->showMessage("SVM model is over"+("SVM_C="+QString::number(i+C_lower)+"_gamma="+QString::number(j+Gamma_lower)+"_model.xml"));
        }
    }
}

void MainWindow::on_gridTest_pushButton_clicked()
{
    //for grid search test
    QStringList fileNames = fileDialog->getOpenFileNames(this, tr("Open Model File"), ".", tr("Model Files(*.xml)"));
    QStringList fileNamesData = fileDialog->getOpenFileNames(this, tr("Open image File"), ".", tr("Image Files(*.jpg)"));

    if(fileNames.isEmpty())
        return;
    if(fileNamesData.isEmpty())
        return;

    ML->openFile(fileNamesData,srcRawTest,srcLabelTest);
    ML->reshapeCombineImages(srcRawTest,testData,srcLabelTest,testLabel);
    ui->statusBar->showMessage("Opened test data "+QString::number(fileNames.size())+" files.");

    QFile file("result.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    cv::Mat PCATestData;
    if(ui->PCA_checkBox->isChecked())
    {
        ML->PCAProject("PCA_Model.txt",testData,PCATestData);
    }
    else
    {
        PCATestData = testData.clone();
    }

    for(int i=0;i<fileNames.size();i++)
    {
        QTime count;
        count.start();
        CF->SVMLoad(fileNames[i]);
        float accurary = 0;
        QVector<float> predictLabelTest;
        for(int j=0;j<fileNamesData.size();j++)
        {

            //qDebug() << testDataPCA.cols;
            predictLabelTest.push_back(CF->SVMPredict(PCATestData.row(j)));
            //qDebug() <<srcLabelTest[j] << predictLabelTest[j];
            if(srcLabelTest[j] - predictLabelTest[j] < 0.5)
                accurary++;
        }
        qDebug() << fileNames[i] <<"-" << accurary/(float)fileNamesData.size()<< "\t" << count.elapsed();
        out << i << "\t"<< accurary/(float)fileNamesData.size() << "\t" << count.elapsed() << "\n";
    }

}
