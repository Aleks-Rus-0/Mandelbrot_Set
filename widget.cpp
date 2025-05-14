#include "widget.h"
#include "./ui_widget.h"
#include <QDebug>
#include <QString>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    x_0 = Width / 2;
    y_0 = Height / 2;
    len_cell = 300;
    quality = 2;
    rubberBand = nullptr;
    ui->setupUi(this);
    //
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    QPen pen(Qt::black, 2);
    paint.setPen(pen);

    for (int i = 0; i < width(); i += quality) {
        for (int j = 0; j < height(); j += quality) {
            std::complex<double> c = to_Complex(i, j);
            std::complex<double> z(0, 0);
            for (int l = 0; l < 100; ++l) {
                z = z * z + c;
                if (abs_complex2(z) - 4 > 0) {
                    paint.fillRect(i, j, quality, quality, QBrush{QColor(1.5 * l, 2.5 * l, 2 * l)});
                    paint.setPen(pen);
                    break;
                }
            }
            if (abs_complex2(z) - 4 <= 0) {
                paint.fillRect(i, j, quality, quality, QBrush{QColor(0, 0, 0)});
            }
        }
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    origin = event->pos();
    if (!rubberBand) {
        rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
    }
    rubberBand->setGeometry(QRect(origin, QSize()));
    rubberBand->show();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    rubberBand->setGeometry(QRect(origin, event->pos()).normalized());
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    rubberBand->hide();
    QPoint finish = event->pos();

    if (abs(finish.ry() - origin.ry()) > abs(finish.rx() - origin.rx())) {
        int len_cell_ = width() / abs(to_Complex(finish.ry(), 0).real() - to_Complex(origin.ry(), 0).real());

        x_0 = (-to_Complex(abs(finish.rx() - origin.rx()) / 2 + std::min(finish.rx(), origin.rx()), 0).real()) * len_cell_
              + abs(finish.rx() - origin.rx()) / 2 + std::min(finish.rx(), origin.rx());
        y_0 = (-to_Complex(0, abs(finish.ry() - origin.ry()) / 2 + std::min(finish.ry(), origin.ry())).imag()) * len_cell_
              + abs(finish.ry() - origin.ry()) / 2 + std::min(finish.ry(), origin.ry());
        len_cell = len_cell_;
    } else {
        int len_cell_ = height() / abs(to_Complex(finish.rx(), 0).real() - to_Complex(origin.rx(), 0).real());

        x_0 = (-to_Complex(abs(finish.rx() - origin.rx()) / 2 + std::min(finish.rx(), origin.rx()), 0).real()) * len_cell_
              + abs(finish.rx() - origin.rx()) / 2 + std::min(finish.rx(), origin.rx());
        y_0 = (-to_Complex(0, abs(finish.ry() - origin.ry()) / 2 + std::min(finish.ry(), origin.ry())).imag()) * len_cell_
              + abs(finish.ry() - origin.ry()) / 2 + std::min(finish.ry(), origin.ry());
        len_cell = len_cell_;
    }

    x_0 -= (abs(finish.rx() - origin.rx()) / 2 + std::min(finish.rx(), origin.rx()) - width() / 2);
    y_0 -= (abs(finish.ry() - origin.ry()) / 2 + std::min(finish.ry(), origin.ry()) - height() / 2);
    repaint();
}

std::complex<double> Widget::to_Complex(int x, int y)
{
    return std::complex<double> ((x - x_0) * 1.0 / len_cell, (y - y_0) * 1.0 / len_cell);
}
