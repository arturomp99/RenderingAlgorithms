#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Load model
    connect(ui->loadModelBtn, SIGNAL(clicked()), ui->openglWidget, SLOT(chooseModel()));

    // Change scene
    connect(ui->actionScenePhong, &QAction::triggered, this, [=](void){ changeScene(new ScenePhong()); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show()
{
    QMainWindow::show();
    if (!ui->openglWidget->loadModel("../RenderingAlgorithms/models/sphere.ply")) // By default, show the sphere.ply model
        QMessageBox::warning(this, tr("Error"), tr("The file could not be opened"));
}

void MainWindow::changeScene(Scene *sc)
{
    // First set scene to glwidget. This will trigger deleting old scene and its associated widget.
    // Otherwise, qDeleteAll deletes the widget first, and then the scene destructor crashes
    ui->openglWidget->setScene(sc);
    qDeleteAll(ui->sceneOptions->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
    ui->sceneOptions->layout()->addWidget(sc->sceneUI());
}
