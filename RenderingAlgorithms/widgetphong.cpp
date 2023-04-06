#include "widgetphong.h"
#include "ui_widgetphong.h"

WidgetPhong::WidgetPhong(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetPhong)
{
    ui->setupUi(this);
}

WidgetPhong::~WidgetPhong()
{
    delete ui;
}
