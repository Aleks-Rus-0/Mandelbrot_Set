#include "widget.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QSlider>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget *window = new QWidget;
    window->setWindowTitle("Mandelbrot Set");


    Widget *w = new Widget;
    w->setFixedSize(Width, Height);

    QPalette Pal; Pal.setColor(QPalette::Window, Qt::white);
    w->setAutoFillBackground(true);
    w->setPalette(Pal);

    QSlider *slider = new QSlider;
    slider->setRange(1, MAX_value_slider - 1);
    slider->setValue(4);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(w);
    layout->addWidget(slider);

    QObject::connect(slider, SIGNAL(valueChanged(int)), w, SLOT(set_quality(int)));

    window->setLayout(layout);

    window->show();
    return a.exec();
}
