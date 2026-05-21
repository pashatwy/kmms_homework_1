#pragma onced
#include "MovingObject.hpp"

class Mario : public MovingObject {
	protected: 
		bool isFly;
	public:
		Mario(float xPos, float yPos, float oWidth, float oHeight, char type);
	
		bool getIsFly() const;
		
		void setIsFly( bool newIsFly );
		
		void updatePhysics(Map& map, GameObject** allObjects, int count) override;
};