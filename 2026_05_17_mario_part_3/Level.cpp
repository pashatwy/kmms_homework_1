#include "Level.hpp"
#include "Brick.hpp"
#include <windows.h>
#include <cmath>

Level::Level(int width, int height) 
    : levelMap(width, height), player(nullptr), gameObjects(nullptr), objectsCount(0) 
{
    player = new Mario(39.0f, 10.0f, 3.0f, 3.0f, '@');

    objectsCount = 2;
    gameObjects = new GameObject*[objectsCount];

    gameObjects[0] = new Brick(0.0f, 20.0f, 120.0f, 5.0f, '#');
    gameObjects[1] = new Brick(45.0f, 12.0f, 4.0f, 2.0f, '?');
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
    if (player == nullptr) return;

    player->setIsFly(true);

    player->setVertSpeed(player->getVertSpeed() + 0.05f);
    player->setY(player->getY() + player->getVertSpeed());

    for (int i = 0; i < objectsCount; i++) {
        if (gameObjects[i] != nullptr && player->isCollision(*gameObjects[i])) {
            
            if (player->getVertSpeed() > 0) {
                player->setIsFly(false);
                player->setY(gameObjects[i]->getY() - player->getHeight());
                player->setVertSpeed(0);
            }

            else if (player->getVertSpeed() < 0) {
                player->setY(gameObjects[i]->getY() + gameObjects[i]->getHeight());
                player->setVertSpeed(0);
            }
            break;
        }
    }
}

bool Level::update() {
    bool needRender = false;

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

    float oldY = player->getY();
    updatePhysics();

    if (player->getY() != oldY || player->getVertSpeed() != 0) {
        needRender = true;
    }

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