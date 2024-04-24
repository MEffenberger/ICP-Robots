#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::customButtonSlot);
    ui->tableWidget->verticalHeader()->setVisible(false); // Hides the row numbers
    ui->tableWidget->horizontalHeader()->setVisible(false); // Hides the column letters/numbers
    this->setFixedSize(QSize(1200, 720));

}

MainWindow::~MainWindow()
{
    delete ui;
}

// void MainWindow::on_pushButton_3_clicked()
// {
//     QApplication::quit();
// }

// Constructor

void MainWindow::customButtonSlot()
{
    QApplication::quit();
}

// void CustomGraphicsView::drawGrid() {
//     const int gridSize = 10; // Size of the grid
//     QGraphicsScene *scene = new QGraphicsScene(this);
//     setScene(scene);

//     // Calculate the number of lines needed based on the view size and grid size
//     int numLinesX = width() / gridSize;
//     int numLinesY = height() / gridSize;

//     // Draw the horizontal lines
//     for(int i = 0; i < numLinesY; ++i) {
//         scene->addLine(0, i * gridSize, width(), i * gridSize, QPen(Qt::gray));
//     }

//     // Draw the vertical lines
//     for(int i = 0; i < numLinesX; ++i) {
//         scene->addLine(i * gridSize, 0, i * gridSize, height(), QPen(Qt::gray));
//     }
// }

