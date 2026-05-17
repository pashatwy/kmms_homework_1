#include "GameObject.hpp"
#include <cmath>

GameObject::GameObject(float xPos, float yPos, float oWidth, float oHeight, char type) {
    x = xPos;
    y = yPos;
    width = oWidth;
    height = oHeight;
    vertSpeed = 0;
    horizonSpeed = 0.2f;
    cType = type;
}

GameObject::~GameObject() {}

void GameObject::update() {
    x += horizonSpeed;
    y += vertSpeed;
}

void GameObject::draw(char **map, const int mapWidth, const int mapHeight) const {
    int ix = (int)round(x);
    int iy = (int)round(y);
    int iWidth = (int)round(width);
    int iHeight = (int)round(height);
    
    for (int i = ix; i < (ix + iWidth); i++) {
        for (int j = iy; j < (iy + iHeight); j++) {
            if (isPosInMap(i, j, mapWidth, mapHeight)) {
                map[j][i] = cType;
            }
        }
    }
}

bool GameObject::isCollision(const GameObject& other) const {
    return (x + width > other.getX()) && (x < other.getX() + other.getWidth()) &&
           (y + height > other.getY()) && (y < other.getY() + other.getHeight());
}

Brick::Brick(float xPos, float yPos, float oWidth, float oHeight, char type)
    : GameObject(xPos, yPos, oWidth, oHeight, type) {}
void Brick::update() {
}

Mario::Mario(float xPos, float yPos, float oWidth, float oHeight, char type)
    : GameObject(xPos, yPos, oWidth, oHeight, type) {
    isFly = false;
}
void Mario::update() {
    vertSpeed += 0.05f;
    y += vertSpeed;
    
    if (y > 20) {
        y = 20;
        vertSpeed = 0;
    }
}

Enemy::Enemy(float xPos, float yPos, float oWidth, float oHeight, char type)
    : GameObject(xPos, yPos, oWidth, oHeight, type) {}
void Enemy::update() {
	vertSpeed +=0.05f;
	y += vertSpeed;
    if (y > 20) {
        y = 20;
        vertSpeed = 0;
    }
}