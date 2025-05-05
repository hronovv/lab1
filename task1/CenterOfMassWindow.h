// CenterOfMassWindow.h
#ifndef CENTER_OF_MASS_WINDOW_H
#define CENTER_OF_MASS_WINDOW_H
#include "window.h"

class CenterOfMassWindow : public QWidget {
    Q_OBJECT

public:
    explicit CenterOfMassWindow(const QPoint &center, Window* mainWindow, QWidget *parent = nullptr)
        : QWidget(parent) {
        setWindowTitle("Центр масс");
        QLabel *label = new QLabel("Центр масс: (" + QString::number(center.x()) + ", " + QString::number(center.y()) + ")", this);
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(label);

        QPushButton *closeButton = new QPushButton("Закрыть", this);
        connect(closeButton, &QPushButton::clicked, this, [mainWindow, this]() {
            mainWindow->clearCenterOfMassPoint(); // Clear the center point in main window
            this->close(); // Close this window
        });
        layout->addWidget(closeButton);

        setLayout(layout);
    }
};

#endif // CENTER_OF_MASS_WINDOW_H
