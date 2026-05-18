#pragma once

class GameObject {
protected:
    float x, y;
    float width, height;
    char cType;

public:
    GameObject(float xPos, float yPos, float oWidth, float oHeight, char type);
    virtual ~GameObject();

    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;
    char getType() const;

    void setX(float newX);
    void setY(float newY);

    virtual void update(); //хз
    void draw(char **map, const int mapWidth, const int mapHeight) const;
    bool isCollision(const GameObject& other) const;
};

class Brick : public GameObject {
public:
    Brick(float xPos, float yPos, float oWidth, float oHeight, char type);
    void update() override;
};