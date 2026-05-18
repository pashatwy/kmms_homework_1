#pragma once
#include "GameObject.hpp"

class MovingObject : public GameObject {
	protected:
		float vertSpeed;
		float horizonSpeed;
	public:
		MovingObject(float xPos, float yPos, float oWidth, float oHeight, char type);
		
		float getVertSpeed() const;
		float getHorizonSpeed() const;
		
		void setVertSpeed( float newVertSpeed );
		void setHorizonSpeed( float newHorizonSpeed );
		
		void update() override;
};