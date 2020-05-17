#ifndef RADARSCANNING_H
#define RADARSCANNING_H

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>

class RadarScanning : public QWidget
{
	Q_OBJECT

	struct PosStruct
	{
		QPoint pos;
		int animation;
	};

public:
	RadarScanning(QWidget *parent = nullptr);
protected:
	void paintEvent(QPaintEvent* e) override;
	void resizeEvent(QResizeEvent* e) override;

    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent *e)override;
    void mouseDoubleClickEvent(QMouseEvent*e) override;

    void keyPressEvent(QKeyEvent *e) override;

private:
	void drawBackground(QPainter&);
	void drawScanning(QPainter&);
	void drawScale(QPainter& pai);
	void drawLock(QPainter&, PosStruct&);

	int m_r = 0;
	QPixmap* bg;

    QPoint point;

	QTimer* animation_time = nullptr;
	int arc = 280;



	std::vector<PosStruct> *vec;

private slots:
	void timeOut();
};

#endif // !RADARSCANNING_H
