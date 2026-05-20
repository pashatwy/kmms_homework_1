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

    virtual void update();
    bool isCollision(const GameObject& other) const;
};