#ifndef CLUTTERMASK_H
#define CLUTTERMASK_H

#include <QWidget>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class ClutterMask; }
QT_END_NAMESPACE

class ClutterMask : public QWidget
{
    Q_OBJECT

public:
    ClutterMask(QWidget *parent = nullptr);
    ~ClutterMask();

public slots:
    void paintEvent(QPaintEvent*);

private:
    Ui::ClutterMask *ui;
    QTimer* m_timer;

    QVector<QPoint> clutterContainer;
    QPoint top_left;
    QPoint randomCircleCoordinate;

private:
    int m_cellsPerEdge = 30;
    int m_cellSize = 15;
    int m_gridSize = m_cellsPerEdge * m_cellsPerEdge;
    int circleCount = m_gridSize * 100 / 100; //40% of the grid is going to be filled with circles
    int m_percentage;

private:
    QVector<QPoint> ignoredClutters(QVector<QPoint> clutterContainer, int percentage);

};
#endif // CLUTTERMASK_H
