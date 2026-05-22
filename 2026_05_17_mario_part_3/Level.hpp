#include "Map.hpp"
#include "Mario.hpp"
#include "GameObject.hpp"

class Level {
private:
    Map levelMap;
    Mario* player;
    GameObject** gameObjects;
	int capacity;
    int count;
	
	void updatePhysics(GameObject** all, int totalCount);
	void growArray();

public:
    Level(int width, int height);
    ~Level();
	
	void removeGameObject(int index);
	void handleWorldEvents();
	void spawnCoin(float x, float y);
	void addGameObject(GameObject* gameObjectsbj);
    bool update();
    void render();
};