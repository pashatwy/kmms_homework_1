#include "Mario.hpp"

Mario::Mario(
	float xPos, float yPos,
	float oWidth, float oHeight,
	char type)
	: MovingObject(xPos, yPos, oWidth, oHeight, type){
		isFly = false;
}

bool Mario::getIsFly() const { return isFly; }

void Mario::setIsFly( bool newIsFly ){
	isFly = newIsFly;
}

void Mario::update() {
    isFly = true; 
    vertSpeed += 0.05f;
    y += vertSpeed;
}
