#include "Level.hpp"
#include "Brick.hpp"
#include "Enemy.hpp"
#include "Coin.hpp"
#include <windows.h>
#include <cmath>
#include <iostream>

Level::Level(int width, int height) 
    : levelMap(width, height), player(nullptr), gameObjects(nullptr), capacity(10), count(0) 
{
    player = new Mario(39.0f, 10.0f, 3.0f, 3.0f, '@');

    gameObjects = new GameObject*[capacity];
    for (int i = 0; i < capacity; i++) gameObjects[i] = nullptr;

    addGameObject(new Brick(0.0f, 20.0f, 120.0f, 5.0f, '#'));
    addGameObject(new Brick(45.0f, 12.0f, 4.0f, 2.0f, '?'));
    addGameObject(new Brick(60.0f, 15.0f, 40.0f, 10.0f, '#'));
    addGameObject(new Enemy(25.0f, 10.0f, 3.0f, 2.0f, 'o'));
}

Level::~Level() {
    delete player;
    if (gameObjects != nullptr) {
        for (int i = 0; i < count; i++) { 
            if (gameObjects[i] != nullptr) {
                delete gameObjects[i];
            }
        }
        delete[] gameObjects;
    }
}

void Level::removeGameObject(int index) {
    if (index < 0 || index >= count) return;

    delete gameObjects[index];
    
    for (int i = index; i < count - 1; i++) {
        gameObjects[i] = gameObjects[i + 1];
    }
    
    gameObjects[count - 1] = nullptr;
    count--;
}

void Level::handleWorldEvents() {
    if (player->hitBlock != nullptr) {
        if (player->hitBlock->getType() == '?') {
            player->hitBlock->setType('-');
            spawnCoin(player->hitBlock->getX(), player->hitBlock->getY());
        }
		player->hitBlock = nullptr;
    }

    for (int i = 0; i < count; i++) {
        if (gameObjects[i] != nullptr && gameObjects[i]->getType() == '$') {
            if (player->isCollision(*gameObjects[i])) {
                removeGameObject(i); 
                break;
            }
        }
    }
}

void Level::spawnCoin(float x, float y) {
	Coin* newCoin = new Coin(x, y - 1.0f, 3.0f, 2.0f, '$');
    addGameObject(newCoin);
}

void Level::updatePhysics(GameObject** all, int totalCount) {
    for (int i = 0; i < count; i++) {
        IPhysics* physicalObj = dynamic_cast<IPhysics*>(gameObjects[i]);
        if (physicalObj) {
            physicalObj->updatePhysics(levelMap, all, totalCount);
        }
    }
}

void Level::addGameObject(GameObject* obj) {
    if (count >= capacity) {
        growArray();
    }
    gameObjects[count] = obj;
    count++;
}

void Level::growArray() {
    int newCapacity = capacity * 2;
    GameObject** newArray = new GameObject*[newCapacity];

    for (int i = 0; i < newCapacity; i++) newArray[i] = nullptr;

    for (int i = 0; i < count; i++) {
        newArray[i] = gameObjects[i];
    }

    delete[] gameObjects;
    gameObjects = newArray;
    capacity = newCapacity;
}

bool Level::update() {
    if (!player->getIsFly() && GetKeyState(VK_SPACE) < 0) {
        player->setVertSpeed(-1.0f);
        player->setIsFly(true);
    }
    if (GetKeyState('D') < 0) {
        levelMap.scrollMap(-1.0f, player, gameObjects, count);
    }
    if (GetKeyState('A') < 0) {
        levelMap.scrollMap(1.0f, player, gameObjects, count);
    }

    handleWorldEvents();

    GameObject** allWithPlayer = new GameObject*[count + 1];
    for (int i = 0; i < count; i++) allWithPlayer[i] = gameObjects[i];
    allWithPlayer[count] = player;

    player->updatePhysics(levelMap, allWithPlayer, count + 1);
    updatePhysics(allWithPlayer, count + 1);

    delete[] allWithPlayer;
    return true;
}

void Level::render() {
    levelMap.clear();

    for (int i = 0; i < count; i++) {
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