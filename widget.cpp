#include "widget.h"
#include "ui_widget.h"

#include <QPainter>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(&timer, &QTimer::timeout, [this]
    {
        if (360 == angle) {
            angle = 0;
        }
        ++angle;
        update();
    });

    timer.start(40);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPixmap pix(tr(":/img/xishi.jpeg"));
    QPen pen;
    pen.setWidth(5);
    pen.setColor(Qt::red);
    auto painter = new QPainter(this);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing, true);
    QPoint center_point(this->rect().center());

    painter->save();
    painter->translate(center_point);
    int redius = (std::min(pix.width(), pix.height()) - 10 * 2) / 2;
    painter->setPen(Qt::red);
    painter->drawEllipse(QPoint(0, 0), redius, redius);

    auto rect = QRect(-redius, -redius, redius * 2, redius * 2);
    QRegion region(rect, QRegion::Ellipse);
    pen.setColor(Qt::blue);
    painter->setPen(pen);
    painter->drawArc(rect.adjusted(-3, -3, 3, 3), 0, angle * 16);
    painter->setClipRegion(region);
    painter->rotate(angle);
    painter->drawPixmap(rect, pix);

    painter->restore();
}
