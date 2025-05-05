#ifndef SHAPE_CHARACTERISTICS_WINDOW_H
#define SHAPE_CHARACTERISTICS_WINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class ShapeCharacteristicsWindow : public QWidget {
    Q_OBJECT

public:
    explicit ShapeCharacteristicsWindow(double area, double perimeter,Window* window,QWidget *parent = nullptr)
        : QWidget(parent) {
        setWindowTitle("Характеристики фигуры");

        // Создание и настройка меток
        QLabel *areaLabel = new QLabel("Площадь: " + QString::number(area), this);
        QLabel *perimeterLabel = new QLabel("Периметр: " + QString::number(perimeter), this);

        // Установка стиля меток
        areaLabel->setAlignment(Qt::AlignCenter);
        perimeterLabel->setAlignment(Qt::AlignCenter);

        // Установка компоновки
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(areaLabel);
        layout->addWidget(perimeterLabel);

        // Создание кнопки закрытия
        QPushButton *closeButton = new QPushButton("Закрыть", this);
        connect(closeButton, &QPushButton::clicked, this, &ShapeCharacteristicsWindow::close);
        layout->addWidget(closeButton);

        // Установка компоновки на виджет
        setLayout(layout);

        // Установка фиксированного размера окна
        setFixedSize(250, 120); // Увеличен размер для лучшего отображения

        // Установка отступов для визуального улучшения
        layout->setContentsMargins(10, 10, 10, 10); // Отступы для всего окна
        layout->setSpacing(10); // Внутренние отступы между элементами
    }
};

#endif // SHAPE_CHARACTERISTICS_WINDOW_H
