#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    btnConnect = new QPushButton(this);
    createClient();
    createChart();

    QTimer *timer1 = new QTimer(this);
    connect(timer1, SIGNAL(timeout()),this,SLOT(onPublish1()));
    timer1->start(500);
    connect(btnConnect,SIGNAL(clicked()),this, SLOT(onButtonConnectDisClicked()));
}

void MainWindow::onPublish1()
{
    static pub2 = 0;
    static pub3 = 0;
    m_client1->publish("Topic One","1",1,False);
    drawLine1();
    pub2=pub2+1;

    if(pub1 == 2){
       m_client2->publish("Topic Two","2",1,False);
       drawChart2();
       pub2 = 0;
       pub3=pub3+1;
   }

    if(pub3 == 2){
       m_client3->publish("Topic Three","3",1,False);
       drawChart3();
       pub3 =0;
   }
}

void MainWindow::drawLine1()
{
  static float x1 = 0;
  static int y1 = 0;

  series1->append(x1,y1);
  chart->addSeries(series1);
  x1 = x1+0.5;
  y1 = y1+1;
  if(x1 == 5.0){
     x1 = 0;
     y1 = 0;
  }
}

void MainWindow::drawChart2()
{
  static float x1 = 0;
  static int y1 = 0;
  series2->append(x1,y1);
  chart->addSeries(series2);
  if(x1 == 5.0){
     x1 = 0;
     y1 = 0;
  }

}

void MainWindow::drawChart3()
{
  static float x1 = 0;
  static int y1 = 0;

  series3->append(0,0);
  chart->addSeries(series3);
  if(x1 == 5.0){
     x1 = 0;
     y1 = 0;
  }
}



MainWindow::CreateChart()
{
   series1 = new QLineSeries();
   series2 = new QLineSeries();
   series3 = new QLineSeries();

   series1.setColor(Qt::red);
   series2.setColor(Qt::blue);
   series3.setColor(Qt::green);

   chart = new QChart();
   chart->legend()->hide();
   chart->setTitle("Stream Data Line chart");

   QValueAxis *axisX = new QValueAxis();
   axisX->setRange(0,7);
   chart->addAxis(axisX, Qt::AlignLeft);
   series->attachAxis(axisY);

   QValueAxis *axisY = new QValueAxis();
   axisY->setRange(0,10);
   chart->addAxis(axisY, Qt::AlignLeft);
   series->attachAxis(axisY);

   QChartView *chartView = new QChartView(chart);
   chartView->setRenderHint(QPainter::Antialiasing);
   setCentralWidget(chartView);
   resize(400, 300);
}


void MainWindow::createClient()
{
  m_client1 = new QMqttClient(this);
  m_client1->setHostname("broker.hivemq.com");
  m_client1->setPort(1883);

  m_client2 = new QMqttClient(this);
  m_client2->setHostname("broker.hivemq.com");
  m_client2->setPort(1883);

  m_client3 = new QMqttClient(this);
  m_client3->setHostname("broker.hivemq.com");
  m_client3->setPort(1883);

}

void MainWindow::onButtonConnectDisClicked()
{
    if (m_client1->state() == QMqttClient::Disconnected) {
        btnConnect->setText(tr("Disconnect"));
        m_client1->connectToHost();
    } else {
        btnConnect->setText(tr("Connect"));
        m_client1->disconnectFromHost();
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}
