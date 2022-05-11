#include "cluttermask.h"
#include "ui_cluttermask.h"
#include <QPainter>
#include <QDebug>
#include <QRandomGenerator>
#include <QPoint>
#include <math.h>

ClutterMask::ClutterMask(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClutterMask)
{
    ui->setupUi(this);

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));

    this->clutterContainer = {};

    //x and y values of top_left must be the same!
    top_left.setX(20);
    top_left.setY(20);

    for(int i=0; i<circleCount; i++) //creating random circle coordinates & storing them in container
    {
        int k = QRandomGenerator::global()->bounded(1, m_cellsPerEdge+1);
        int p = QRandomGenerator::global()->bounded(1, m_cellsPerEdge+1);

        randomCircleCoordinate.setX((top_left.x() + k * m_cellSize) - m_cellSize);
        randomCircleCoordinate.setY((top_left.y() + p * m_cellSize) - m_cellSize);

        clutterContainer.insert(clutterContainer.end(), randomCircleCoordinate);
    }

    m_timer->start(2000);
}

ClutterMask::~ClutterMask()
{
    delete ui;
    delete m_timer;
}

QVector<QPoint> ClutterMask::ignoredClutters(QVector<QPoint> clutterContainer ,int percentage)
{
    int edgeSize = m_cellsPerEdge * m_cellSize;
    QPoint gridCenter;

    QVector<QPoint> newClutters;

    gridCenter.setX(top_left.x() + edgeSize / 2);
    gridCenter.setY(top_left.y() + edgeSize / 2);

    double ignoredInterval;
    ignoredInterval = (edgeSize / 2) * (percentage / 100.0);

    for(int i=0; i<clutterContainer.size(); i++ )
    {
        auto diff = clutterContainer[i] - gridCenter;

        auto distance = sqrt( diff.x() * diff.x() + diff.y() * diff.y());

        if(distance > ignoredInterval)
            newClutters.insert(newClutters.end(), clutterContainer[i]);
    }

    return newClutters;
}

void ClutterMask::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPen pen;
    pen.setWidth(1);
    pen.setBrush(Qt::SolidPattern);
    pen.setColor(Qt::green);
    painter.setPen(pen);

    for(int i = 0; i <= m_cellsPerEdge; i++) //drawing the grid
    {
        QPoint p1 = top_left + QPoint(0, m_cellSize * i);
        QPoint p2 = top_left + QPoint(m_cellsPerEdge * m_cellSize, m_cellSize * i);
        QPoint p3 = top_left + QPoint(m_cellSize * i, 0);
        QPoint p4 = top_left + QPoint(m_cellSize * i, m_cellsPerEdge * m_cellSize);

        painter.drawLine(p1, p2);
        painter.drawLine(p3, p4);
    }

    int flip;

    QVector<QPoint> restrictedClutters = ignoredClutters(clutterContainer, 60);

    for(int i=0; i<restrictedClutters.size(); i++)
    {
        painter.setBrush(Qt::black);
        //painter.drawEllipse(restrictedClutters[i].x(),restrictedClutters[i].y(),m_cellSize, m_cellSize);
        //if you uncomment this line, all circles will be visible
        flip = rand() % 2;

        if(flip == 1) //lightening the circles
        {
            painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
            painter.drawEllipse(restrictedClutters[i].x(), restrictedClutters[i].y(), m_cellSize, m_cellSize);
        }
    }
}
