#ifndef WIDGETPHONG_H
#define WIDGETPHONG_H

#include <QWidget>

namespace Ui {
class WidgetPhong;
}

class WidgetPhong : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetPhong(QWidget *parent = nullptr);
    ~WidgetPhong();

private:
    Ui::WidgetPhong *ui;
};

#endif // WIDGETPHONG_H
