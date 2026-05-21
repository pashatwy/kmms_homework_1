#include "Level.hpp"
#include "Brick.hpp"
#include "Enemy.hpp"
#include <windows.h>
#include <cmath>

Level::Level(int width, int height) 
    : levelMap(width, height), player(nullptr), gameObjects(nullptr), objectsCount(0) 
{
    player = new Mario(39.0f, 10.0f, 3.0f, 3.0f, '@');

    objectsCount = 4;
    gameObjects = new GameObject*[objectsCount];

    gameObjects[0] = new Brick(0.0f, 20.0f, 120.0f, 5.0f, '#');
    gameObjects[1] = new Brick(45.0f, 12.0f, 4.0f, 2.0f, '#');
	gameObjects[2] = new Brick(60.0f, 15.0f, 40.0f, 10.0f, '#');
	gameObjects[3] = new Enemy(25.0f, 10.0f, 3.0f, 2.0f, 'o');
}

Level::~Level() {
    delete player;
    
    if (gameObjects != nullptr) {
        for (int i = 0; i < objectsCount; i++) {
            delete gameObjects[i];
        }
        delete[] gameObjects;
    }
}

void Level::updatePhysics() {
    for (int i = 0; i < objectsCount; i++) {
        IPhysics* physicalObj = dynamic_cast<IPhysics*>(gameObjects[i]);
        if (physicalObj) {
            physicalObj->updatePhysics(levelMap, gameObjects, objectsCount);
        }
    }
}

bool Level::update() {
    bool needRender = false;

    player->setHorizonSpeed(0.0f); 

    if (!player->getIsFly() && GetKeyState(VK_SPACE) < 0) {
        player->setVertSpeed(-1.0f);
        player->setIsFly(true);
        needRender = true;
    }

    if (GetKeyState('D') < 0) {
        levelMap.scrollMap(-1.0f, player, gameObjects, objectsCount);
        needRender = true;
    }
    if (GetKeyState('A') < 0) {
        levelMap.scrollMap(1.0f, player, gameObjects, objectsCount);
        needRender = true;
    }
	
	
	if (player) {
		player->updatePhysics(levelMap, gameObjects, objectsCount);
	}

    updatePhysics();


    needRender = true;

    return needRender;
}

void Level::render() {
    levelMap.clear();

    for (int i = 0; i < objectsCount; i++) {
        if (gameObjects[i] != nullptr) {
            int objX = (int)std::round(gameObjects[i]->getX());
            int objY = (int)std::round(gameObjects[i]->getY());
            int objW = (int)std::round(gameObjects[i]->getWidth());
            int objH = (int)std::round(gameObjects[i]->getHeight());

            for (int x = objX; x < objX + objW; x++) {
                for (int y = objY; y < objY + objH; y++) {
                    levelMap.setChar(x, y, gameObjects[i]->getType());
                }
            }
        }
    }

    int pX = (int)std::round(player->getX());
    int pY = (int)std::round(player->getY());
    int pW = (int)std::round(player->getWidth());
    int pH = (int)std::round(player->getHeight());

    for (int x = pX; x < pX + pW; x++) {
        for (int y = pY; y < pY + pH; y++) {
            levelMap.setChar(x, y, player->getType());
        }
    }

    levelMap.display();
}