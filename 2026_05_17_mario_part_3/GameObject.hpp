#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

class GameObject {
protected:
    float x, y;
    float width, height;
    float vertSpeed;
    float horizonSpeed;
    char cType;

public:
    GameObject(float xPos, float yPos, float oWidth, float oHeight, char type);
    virtual ~GameObject();

    float getX() const { return x; }
    float getY() const { return y; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }
    char getType() const { return cType; }

    void setX(float newX) { x = newX; }
    void setY(float newY) { y = newY; }

    virtual void update();
    void draw(char **map, const int mapWidth, const int mapHeight) const;
    bool isCollision(const GameObject& other) const;
};

class Brick : public GameObject {
public:
    Brick(float xPos, float yPos, float oWidth, float oHeight, char type);
    void update() override;
};

class Mario : public GameObject {
private: 
    bool isFly;

public:
    Mario(float xPos, float yPos, float oWidth, float oHeight, char type);
    void update() override;
};

class Enemy : public GameObject {
public:
	Enemy(float xPos, float yPos, float oWidth, float oHeight, char type);
	void update() override;
};

#endif