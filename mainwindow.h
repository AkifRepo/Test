#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QTcpSocket>
#include <QtMqtt/QMqttClient>  //Need Qt updated version.
#include<QPushButton>
#include<QLineSeries>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
       void onButtonConnectDisClicked();

public:
QPushButton *btnConnect;
QMqttClient *m_client;
QLineSeries *series1;
QLineSeries *series2;
QLineSeries *series3;
QChart *chart;
};

#endif // MAINWINDOW_H
