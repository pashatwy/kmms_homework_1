#include "GameObject.hpp"
#include <cmath>

GameObject::GameObject(
	float xPos, float yPos,
	float oWidth, float oHeight,
	char type) {
    x = xPos;
    y = yPos;
    width = oWidth;
    height = oHeight;
    cType = type;
}

GameObject::~GameObject() {}

float GameObject::getX() const { return x; }
float GameObject::getY() const { return y; }
float GameObject::getWidth() const { return width; }
float GameObject::getHeight() const { return height; }
char GameObject::getType() const { return cType; }

void GameObject::setX(float newX) { x = newX; }
void GameObject::setY(float newY) { y = newY; }

void GameObject::update() {} //нужен ли вообще?

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

