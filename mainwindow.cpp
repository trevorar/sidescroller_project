#include "mainwindow.h"

/** Default constructor for MainWindow */
MainWindow::MainWindow() {
	name = "Trevor";
	error = new QErrorMessage;
	
	//MENU BAR
	mb = menuBar();
	file = new QMenu("File");
	
  quit = new QAction("Quit", file);
  start = new QAction("Start Game", file);
  
  file->addAction(start);
  file->addAction(quit);
     
  connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
  connect(start, SIGNAL(triggered()), this, SLOT(startSlot()));
  
  mb->addMenu(file);
  
  //TOOL BAR
  toolBar = new QToolBar();
  
  startButton = new QPushButton("Start (F1)");
  quitButton = new QPushButton("Quit (Esc)");
  pauseButton = new QPushButton("Pause (P)");
  
  connect(startButton, SIGNAL(clicked()), this, SLOT(startSlot()));
  connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
  connect(pauseButton, SIGNAL(clicked()), this, SLOT(pause()));
  
  toolBar->addWidget(startButton);
  toolBar->addSeparator();
  toolBar->addWidget(quitButton);
  toolBar->addSeparator();
  toolBar->addWidget(pauseButton);
  
  addToolBar(toolBar);
  
  //TOP WIDGET
  display = new QDockWidget;
  displayWidget = new DisplayWidget;
  display->setWidget(displayWidget);
  addDockWidget(Qt::TopDockWidgetArea, display);
  display->setMaximumSize(1200, 100);
  display->setFeatures(0x00);
  
  //GAME DISPLAY
  title = new InfoScreen(0);
  gameOver = new InfoScreen(1);
  instructions = new InfoScreen(2);
  setCentralWidget(title);
  gameInProgress = 0;
	
	setMinimumSize(1200, 700);
	setMaximumSize(1200, 700);
	
	paused = 0;
	setWindowTitle("MAGIC NINJA");
	setFocus();
}

/** Deconstructor - deallocates all memory from the MainWindow */
MainWindow::~MainWindow() {
	delete error;

	//Deallocation of menu bar
	delete start;
	delete quit;
	delete file;
	
	//Deallocation of game board
	if(gameInProgress) {
		delete game;
	}
}

/** Displays the MainWindow */
void MainWindow::show() {
	QMainWindow::show();
}

//CHANGE THIS
void MainWindow::startSlot() { 
	if(!gameInProgress) {
		game = new GraphicsWindow;
		setCentralWidget(game);
		connect(game->getTimer(), SIGNAL(timeout()), this, SLOT(update()));
		game->start();
		gameInProgress = 1;
	} else if(game->getTimer()->isActive() || paused) {
		delete game;
		game = new GraphicsWindow;
		setCentralWidget(game);
		connect(game->getTimer(), SIGNAL(timeout()), this, SLOT(update()));
		game->start();	
		gameInProgress = 1;
		setFocus();
		return;
	}
	setFocus();
}

void MainWindow::pause() {
	if(game->getTimer()->isActive()) {
		game->getTimer()->stop();
	} else {
		game->getTimer()->start();
	}
	paused = !paused;
	setFocus();
}

void MainWindow::update() {
	displayWidget->setName(name);
	displayWidget->setScore(QString::number(game->getScore()));
	displayWidget->setHealth(QString::number(game->getNinja()->getHealth()));
	displayWidget->setLives(QString::number(game->getNinja()->getLives()));
	
	if(game->gameOver()) {
		gameInProgress = 0;
		pause();
		delete game;
		gameOver = new InfoScreen(1);
		setCentralWidget(gameOver);
	}
	
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
	if(gameInProgress) {
		if(e->key() ==  Qt::Key_D) {
			game->getNinja()->moveRight();
		}
		if(e->key() == Qt::Key_A) {
			game->getNinja()->moveLeft();
		}
		if(e->key() == Qt::Key_W) {
			game->getNinja()->jump();
		}
		if(e->key() ==  Qt::Key_Right) {
			game->fireball(0);
		}
		if(e->key() == Qt::Key_Left) {
			game->fireball(1);
		}
		if(e->key() == Qt::Key_Up) {
			game->fireball(2);
		}
		if(e->key() == Qt::Key_Down) {
			game->fireball(3);
		}
		if(e->key() == Qt::Key_P) {
			pause();
		}
	}
	if(e->key() == Qt::Key_F1) {
		startSlot();
	}
	if(e->key() == Qt::Key_Escape) {
		qApp->quit();
	}
}

void MainWindow::keyReleaseEvent(QKeyEvent *e) {
	if(gameInProgress) {
		if(e->key() ==  Qt::Key_D || e->key() == Qt::Key_A) {
			game->getNinja()->stop();
		}
	}
}
