#include "Mario.hpp"

Mario::Mario(
	float xPos, float yPos,
	float oWidth, float oHeight,
	char type)
	: MovingObject(xPos, yPos, oWidth, oHeight, type){
		isFly = false;
}

bool Mario::getIsFly() const { return isFly; }

void Mario::update() { //временно так
    vertSpeed += 0.05f;
    y += vertSpeed;
    
    if (y > 20) {
        y = 20;
        vertSpeed = 0;
    }
}
