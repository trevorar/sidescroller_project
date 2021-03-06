/** A class to hold the start screen and game over screen
	@author Trevor
*/
#ifndef INFOSCREEN_H
#define INFOSCREEN_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QImage>

class InfoScreen : public QGraphicsView {
	Q_OBJECT
	
	public:
		InfoScreen(int type);
		~InfoScreen();
		
	private:
    QGraphicsScene *scene;
    QImage *background;
};

#endif
