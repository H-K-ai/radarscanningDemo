#include "RadarScanning.h"

#include <cmath>
#include <QPalette>
#include <QPainter>
#include <QTimer>
#include <QPen>
#include <QDebug>

RadarScanning::RadarScanning(QWidget *parent)
	: QWidget(parent)
{
    srand((unsigned)time_t(nullptr));
    bg = new QPixmap(":/image/bk1.jpg");
    bg->fill(Qt::transparent); //set bk hide
    this->resize(bg->size() * 3 / 2);


    setWindowFlags(Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground);// set transparent

	animation_time = new QTimer(this);
	connect(animation_time, &QTimer::timeout, this, &RadarScanning::timeOut);
    animation_time->setInterval(60);
	animation_time->start();

	vec = new std::vector<PosStruct>;
	vec->reserve(10);
}

void RadarScanning::paintEvent(QPaintEvent* e)
{
    Q_UNUSED(e);
	QPainter pai(this);
	pai.setRenderHint(QPainter::Antialiasing);
    pai.fillRect(rect(), QColor(5,236,244,10));

//	for (auto item = vec->begin(); item != vec->end(); ++item)
//		drawLock(pai, *item);
    for (auto &item:*vec) // c++11--new method
        drawLock(pai, item);

	drawBackground(pai);
	drawScanning(pai);
	drawScale(pai);
}

void RadarScanning::resizeEvent(QResizeEvent* e)
{
    Q_UNUSED(e);
	QPalette pal = this->palette();
	pal.setBrush(QPalette::Background, QBrush(bg->scaled(this->size())));
	this->setPalette(pal);

	m_r = (width() > height() ? height() : width()) / 2 - 40;
}

void RadarScanning::drawBackground(QPainter& pai)
{
	// ª≠–Èœﬂ‘≤»¶
 //   pai.setPen(QPen(Qt::green, 3.0, Qt::DotLine));
    pai.setPen(QPen(QColor(5,236,244),2.0,Qt::DotLine));
	pai.drawEllipse(this->rect().center(), m_r / 5 * 1, m_r / 5 * 1);
	pai.drawEllipse(this->rect().center(), m_r / 5 * 2, m_r / 5 * 2);
	pai.drawEllipse(this->rect().center(), m_r / 5 * 3, m_r / 5 * 3);
	pai.drawEllipse(this->rect().center(), m_r / 5 * 4, m_r / 5 * 4);

 //   pai.setPen(QPen(Qt::green, 3.0, Qt::SolidLine));
    pai.setPen(QPen(QColor(5,236,244),3.0,Qt::SolidLine));
	pai.drawEllipse(this->rect().center(), m_r, m_r);
//    pai.setPen(QPen(Qt::green, 3.0, Qt::DotLine));
    pai.setPen(QPen(QColor(5,236,244),3.0, Qt::DotLine));
    pai.drawEllipse(this->rect().center(), m_r - 10, m_r - 10);



	// ª≠Õ¯∏Ò
 //   pai.setPen(QPen(Qt::green, 0.2, Qt::SolidLine));
    pai.setPen(QPen(QColor(5,236,244),0.2,Qt::SolidLine));
	for (int i = 0; i < 10; i++)
	{
		int w = sqrt(pow(m_r, 2) - pow(m_r / 10 * i, 2));
		int h = m_r / 10 * i;
		pai.drawLine(QPoint(this->width() / 2 - w, this->height() / 2 - h), QPoint(this->width() / 2 + w, this->height() / 2 - h));
		pai.drawLine(QPoint(this->width() / 2 - w, this->height() / 2 + h), QPoint(this->width() / 2 + w, this->height() / 2 + h));

		h = sqrt(pow(m_r, 2) - pow(m_r / 10 * i, 2));
		w = m_r / 10 * i;
		pai.drawLine(QPoint(this->width() / 2 - w, this->height() / 2 - h), QPoint(this->width() / 2 - w, this->height() / 2 + h));
		pai.drawLine(QPoint(this->width() / 2 + w, this->height() / 2 - h), QPoint(this->width() / 2 + w, this->height() / 2 + h));
	}

	// ª≠æ‡¿Î
	int value = 300;
	for (int i = 1; i < 5; i++)
	{
		pai.drawText(QPoint(this->width() / 2 - 15, this->height() / 2 - m_r / 5 * i - 2), QString::number(value));
		pai.drawText(QPoint(this->width() / 2 - 15, this->height() / 2 + m_r / 5 * i + 14), QString::number(value));
		value += 200;
	}
}

void RadarScanning::drawLock(QPainter& pai, PosStruct &ps)
{
//	pai.setPen(QPen(Qt::yellow, 2, Qt::SolidLine));
    pai.setPen(QPen(QColor(5,236,244,200), 2.0, Qt::SolidLine));

	int r = m_r / 8;
	if (ps.animation - 40 > r)
	{
		ps.animation -= 40;
		r = ps.animation;
	}

	pai.drawArc(QRect(QPoint(ps.pos.x() - r, ps.pos.y() - r),
		QSize(r * 2, r * 2)), (arc + 90 * 0) * 16, 70 * 16);
	pai.drawArc(QRect(QPoint(ps.pos.x() - r, ps.pos.y() - r),
		QSize(r * 2, r * 2)), (arc + 90 * 1) * 16, 70 * 16);
	pai.drawArc(QRect(QPoint(ps.pos.x() - r, ps.pos.y() - r),
		QSize(r * 2, r * 2)), (arc + 90 * 2) * 16, 70 * 16);
	pai.drawArc(QRect(QPoint(ps.pos.x() - r, ps.pos.y() - r),
		QSize(r * 2, r * 2)), (arc + 90 * 3) * 16, 70 * 16);

//	QColor color(Qt::yellow);
    QColor color(5,236,244,200);
	color.setAlpha(100);
	pai.setPen(QPen(color, r / 4.5, Qt::SolidLine));

	int offset = r / 4.5 * 3;
	pai.drawArc(QRect(QPoint(ps.pos.x() - r + offset / 2, ps.pos.y() - r + offset / 2),
		QSize(r * 2 - offset, r * 2 - offset)), (arc + 90 * 0 + 5) * 16, 60 * 16);
	pai.drawArc(QRect(QPoint(ps.pos.x() - r + offset / 2, ps.pos.y() - r + offset / 2),
		QSize(r * 2 - offset, r * 2 - offset)), (arc + 90 * 1 + 5) * 16, 60 * 16);
	pai.drawArc(QRect(QPoint(ps.pos.x() - r + offset / 2, ps.pos.y() - r + offset / 2),
		QSize(r * 2 - offset, r * 2 - offset)), (arc + 90 * 2 + 5) * 16, 60 * 16);
	pai.drawArc(QRect(QPoint(ps.pos.x() - r + offset / 2, ps.pos.y() - r + offset / 2),
		QSize(r * 2 - offset, r * 2 - offset)), (arc + 90 * 3 + 5) * 16, 60 * 16);

//	pai.setPen(QPen(Qt::yellow, 2, Qt::SolidLine));
    pai.setPen(QPen(QColor(5,236,244,200),2.0,Qt::SolidLine));
	pai.drawLine(QPoint(ps.pos.x() - r / 10, ps.pos.y()), QPoint(ps.pos.x() + r / 10, ps.pos.y()));
	pai.drawLine(QPoint(ps.pos.x(), ps.pos.y() - r / 10), QPoint(ps.pos.x(), ps.pos.y() + r / 10));

	if (ps.pos.x() < width() / 2)
	{
		pai.drawLine(ps.pos.x() - r * 0.7 - 5, ps.pos.y() - r * 0.70 - 5, ps.pos.x() - r - 10, ps.pos.y() - r - 10);
		pai.drawLine(ps.pos.x() - r - 10, ps.pos.y() - r - 10, ps.pos.x() - r - 50, ps.pos.y() - r - 10);
		pai.drawText(ps.pos.x() - r - 160, ps.pos.y() - r - 5, QString("X:%1 Y:%2").arg(ps.pos.x()).arg(ps.pos.y()));
	}
	else
	{
		pai.drawLine(ps.pos.x() + r * 0.7 + 5, ps.pos.y() - r * 0.70 - 5, ps.pos.x() + r + 10, ps.pos.y() - r - 10);
		pai.drawLine(ps.pos.x() + r + 10, ps.pos.y() - r - 10, ps.pos.x() + r + 50, ps.pos.y() - r - 10);
		pai.drawText(ps.pos.x() + r + 50, ps.pos.y() - r - 5, QString("X:%1 Y:%2").arg(ps.pos.x()).arg(ps.pos.y()));
	}
}

void RadarScanning::drawScanning(QPainter& pai)
{
	// ª≠…®√Ë’Î
	QConicalGradient conical(this->width() / 2, this->height() / 2, arc);
  //  QColor color1("#00FF00");
    // ±∏”√—’…´ ¿∂…´ 1C86EE //
    QColor color1("#AFEEEE");
    color1.setAlpha(200);
	QColor color2("#000000");
	color2.setAlpha(0);

	conical.setColorAt(0, color1);
	conical.setColorAt(0.13, color2);

	pai.setPen(Qt::NoPen);
	pai.setBrush(conical);
	pai.drawPie(QRect(QPoint(this->width() / 2 - m_r, this->height() / 2 - m_r), QSize(m_r * 2, m_r * 2)), arc * 16, 60 * 16);
}

void RadarScanning::drawScale(QPainter &pai)
{
	pai.save();
 //   pai.setPen(QPen(Qt::green, 2.0, Qt::SolidLine));
    pai.setPen(QPen(QColor(5,236,244),2.0,Qt::SolidLine));
//  pai.setPen(Qt::green);
//  pai.setPen(QColor(65,132,159));
	pai.translate(this->width() / 2, this->height() / 2);
	int value = 15;

	for (int i = 0; i < 24; i++)
	{
		pai.rotate(360 / 24);
		pai.drawText(QPoint(0, -m_r - 4), value == 360 ? "0" : QString::number(value));
		value += 15;
	}

	for (int i = 0; i < 120; i++)
	{
		pai.rotate(3);
		pai.drawLine(QPoint(0, m_r - 10), QPoint(0, m_r));
	}

	pai.restore();
}

void RadarScanning::timeOut()
{
	arc -= 3;
	if (arc == 0)
		arc = 360;

	if (rand() % 50 == 0)
	{
		PosStruct tmp;
		int r = rand() % m_r;
		tmp.pos.setX(r * cos(arc * 3.1415926 / 180) + this->width() / 2);
		tmp.pos.setY(-r * sin(arc * 3.1415926 / 180) + this->height() / 2);
		tmp.animation = width() > height() ? height() / 2 : width() / 2;
		vec->push_back(tmp);
	}
	
	this->update();
}


void RadarScanning::mousePressEvent(QMouseEvent *e)
{
    point = e->globalPos();
}

void RadarScanning::mouseMoveEvent(QMouseEvent *e)
{
    int dx=e->globalX()-point.x();
    int dy=e->globalY()-point.y();
    point=e->globalPos();
    move(x()+dx,y()+dy);


}

void RadarScanning::mouseReleaseEvent(QMouseEvent *e)
{
    int dx=e->globalX()-point.x();
    int dy=e->globalY()-point.y();
    move(x()+dx,y()+dy);

}


void RadarScanning::mouseDoubleClickEvent(QMouseEvent *e)
{
    static QPoint mousePoint;
    if (e->button() == Qt::LeftButton)
    {
        mousePoint = e->globalPos() - this->pos();
       if(windowState()!= Qt::WindowFullScreen)
       {
          setWindowState(Qt::WindowFullScreen);
       }

       else
       {
          setWindowState(Qt::WindowNoState);
       }

    }
}

void RadarScanning::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())

    {
      case Qt::Key_Escape:
           this->close();
           break;
     default:
        QWidget::keyPressEvent(e);
    }
}





