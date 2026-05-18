#pragma once
#include "MovingObject.hpp"

class Enemy : public MovingObject {
	public:
		Enemy(float xPos, float yPos, float oWidth, float oHeight, char type);
		
		void update() override;
};