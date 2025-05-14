#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QMouseEvent>
#include <QWheelEvent>

#include <QPainter>
#include <QPen>
#include <QRubberBand>
#include <QRect>
#include <QPoint>

#include <complex>

#include "constant.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    std::complex<double> to_Complex(int x, int y);

    double abs_complex(std::complex<double> Z) {
        return sqrt(Z.imag() * Z.imag() + Z.real() * Z.real());
    }
    double abs_complex2(std::complex<double> Z) {
        return Z.imag() * Z.imag() + Z.real() * Z.real();
    }

    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
protected slots:
    void set_quality(int x) {
        quality = MAX_value_slider - x;
        repaint();
    }
private:
    Ui::Widget *ui;
    int len_cell;
    int x_0, y_0;
    int quality;

    double eps = 1e-6;

    QPoint origin;
    QRubberBand *rubberBand;
};
#endif // WIDGET_H
