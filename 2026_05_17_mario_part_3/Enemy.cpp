#include "Enemy.hpp"

Enemy::Enemy(
	float xPos, float yPos,
	float oWidth, float oHeight,
	char type)
	: MovingObject(xPos, yPos, oWidth, oHeight, type){
		vertSpeed = 0;
		horizonSpeed = 0.2;
}

void Enemy::update() {
    x += horizonSpeed;
    y += vertSpeed;
}
	