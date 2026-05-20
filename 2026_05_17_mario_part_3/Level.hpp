#include "Map.hpp"
#include "Mario.hpp"
#include "GameObject.hpp"

class Level {
private:
    Map levelMap;
    Mario* player;
    GameObject** gameObjects;
    int objectsCount;

    void updatePhysics();

public:
    Level(int width, int height);
    ~Level();

    bool update();
    void render();
};