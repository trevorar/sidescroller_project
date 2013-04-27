#include "graphicswindow.h"
#include <iostream>

using namespace std;

/** Constructor - creates a new GraphicsWindow with either 9 or 16 tiles 
	@param dimension of board (3 or 4)
*/
GraphicsWindow::GraphicsWindow() {
	error = new QErrorMessage();
  scene = new QGraphicsScene();
  setScene(scene);

  counter = 0;
  score = 0;
  
  scene->setSceneRect(0,0,1000,600);
  setMinimumSize(1200, 600);
  setMaximumSize(1200, 600);
  
  setBackgroundBrush(QImage("sprites/background1.png"));
  //setCacheMode(QGraphicsView::CacheBackground);
  timer = new QTimer;
  timer->setInterval(60);
  interval = 50;
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  
  ninja = new Ninja();
  scene->addItem(ninja);
}

/** Deconstructor - deletes the messageBox, tiles, scene and view */
GraphicsWindow::~GraphicsWindow() {
	timer->stop();
	delete timer;
	for(int i = 0; i < thugs.size(); i++) {
		delete thugs[i];
	}
	delete error;
	delete ninja;
	delete scene;
}

Ninja* GraphicsWindow::getNinja() {
	return ninja;
}

void GraphicsWindow::fireball(int direction) {
	Fireball* fire;
	fire = ninja->shoot(direction);
	if(fire != NULL) {
		scene->addItem(fire);
	}
}

int GraphicsWindow::getScore() {
	return score;
}

void GraphicsWindow::start() {
  timer->start();
}

QTimer* GraphicsWindow::getTimer() {
	return timer;
}

void GraphicsWindow::moveThugs() {
	for(int i = 0; i < thugs.size(); i++) {
		thugs[i]->move();
	}
}

void GraphicsWindow::checkDead() {
	for(int i = 0; i < thugs.size(); i++) {
		if(thugs[i]->isDead() == 1) {
			delete thugs[i];
			thugs.remove(i);
			score += 250;
		}
	}
}

bool GraphicsWindow::gameOver() {
	return ninja->getDead();
}

void GraphicsWindow::update() {
	
	checkDead();
	moveThugs();
	
	ninja->update();
	
	counter++;
	if(counter % 5 == 0) {
		score += 100;
	}
	
	if(counter > 500 && interval > 10) {
		interval = (interval * 4) / 5;
		timer->setInterval(interval);
		counter = 0;
	}
	
	for(int i = 0; i < thugs.size(); i++) {
		for(int j = 0; j < ninja->getFire()->size(); j++) {
			if(thugs[i]->collidesWithItem(ninja->getFire()->at(j))) {
				thugs[i]->hit();
				delete ninja->getFire()->at(j);
				ninja->getFire()->remove(j);
			}
		}
	}
	
	for(int i = 0; i < thugs.size(); i++) {
		if(thugs[i]->collidesWithItem(ninja)) {
			ninja->hit();
		}
	}
	
	srand(rand() * rand());
	int num = rand() % 2000;
	switch(num) {
		case 0:
		thugs.push_back(new Creep(0));
		scene->addItem(thugs[thugs.size()-1]);
		break;
		
		case 1:
		thugs.push_back(new Creep(1));
		scene->addItem(thugs[thugs.size()-1]);
		break;
		
		case 2:
		thugs.push_back(new Creep(2));
		scene->addItem(thugs[thugs.size()-1]);
		break;
		
		case 3:
		thugs.push_back(new Creep(3));
		scene->addItem(thugs[thugs.size()-1]);
		break;
		
		case 4:
		thugs.push_back(new Creep(4));
		scene->addItem(thugs[thugs.size()-1]);
		break;
		
		case 5:
		thugs.push_back(new Creep(5));
		scene->addItem(thugs[thugs.size()-1]);
		break;
		
		case 6:
		case 7:
		case 8:
		thugs.push_back(new Jumper(0));
		scene->addItem(thugs[thugs.size()-1]);
		break;
		
		case 9:
		case 10:
		case 11:
		thugs.push_back(new Jumper(1));
		scene->addItem(thugs[thugs.size()-1]);
		break;
		
		case 12:
		case 13:
		case 14:
		thugs.push_back(new Bulldozer(0));
		scene->addItem(thugs[thugs.size()-1]);
		break;
		
		case 15:
		case 16:
		case 17:
		thugs.push_back(new Bulldozer(1));
		scene->addItem(thugs[thugs.size()-1]);
		break;
		
		case 18:
		case 19:
		case 20:
		thugs.push_back(new Boxer(0));
		scene->addItem(thugs[thugs.size()-1]);
		break;
		
		case 21:
		case 22:
		case 23:
		thugs.push_back(new Boxer(1));
		scene->addItem(thugs[thugs.size()-1]);
		break;
		
		case 24:
		thugs.push_back(new Blade(0));
		scene->addItem(thugs[thugs.size()-1]);
		break;
		
		case 25:
		thugs.push_back(new Blade(1));
		scene->addItem(thugs[thugs.size()-1]);
		break;
		
		case 26:
		thugs.push_back(new Blade(2));
		scene->addItem(thugs[thugs.size()-1]);
		break;
		
		case 27:
		thugs.push_back(new Blade(3));
		scene->addItem(thugs[thugs.size()-1]);
		break;
		
		case 28:
		thugs.push_back(new Blade(4));
		scene->addItem(thugs[thugs.size()-1]);
		break;
		
		case 29:
		thugs.push_back(new Blade(5));
		scene->addItem(thugs[thugs.size()-1]);
		break;
	}
}
