#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;

class AbstractFigure {
public:
    float rad;
    Shape* getFigure(int type, float x, float y) {
        float radius = 20 + rand() % 100;
        rad = radius;
        switch(type) {
            case 1:
                return makeCircle(radius, x, y);
                break;
            case 2:{
                float a = 50.0 + rand() % 200;
                float b = 50.0 + rand() % 200;
                rad = (a + b) * 0.25;
                return makeRectangle(Vector2f(a, b), x, y);
                break;
            }
            case 3:{
                return makePolygon(radius, 3, x, y);
                break;
            }
            case 4:{
                return makePolygon(radius, 4, x, y);
                break;
            }
            case 5:{
                return makePolygon(radius, 5, x, y);
                break;
            }
        }
    }

    CircleShape* getBonus(int type, float x, float y){
        float radius = 35;
        switch(type) {
            case 1: {
                CircleShape* increaseVel = new CircleShape(radius);
                increaseVel->setOrigin(radius, radius);
                increaseVel->setOrigin(Vector2f(0, 0));
                increaseVel->setPosition(Vector2f(x, y));
                return increaseVel;
                break;
            }
            case 2: {
                CircleShape* decreaseVel = new CircleShape(radius);
                decreaseVel->setOrigin(radius, radius);
                decreaseVel->setOrigin(Vector2f(0, 0));
                decreaseVel->setPosition(Vector2f(x, y));
                return decreaseVel;
                break;
            }
            case 3: {
                CircleShape* increaseCoord = new CircleShape(radius);
                increaseCoord->setOrigin(radius, radius);
                increaseCoord->setOrigin(Vector2f(0, 0));
                increaseCoord->setPosition(Vector2f(x, y));
                return increaseCoord;
                break;
            }
            case 4: {
                CircleShape* decreaseCoord = new CircleShape(radius);
                decreaseCoord->setOrigin(radius, radius);
                decreaseCoord->setOrigin(Vector2f(0, 0));
                decreaseCoord->setPosition(Vector2f(x, y));
                return decreaseCoord;
                break;
            }
        }

    }

    float getRadius() {
        return rad;
    }

    CircleShape* makeCircle(float radius, float x, float y) {
        CircleShape* circle = new CircleShape(radius);
        circle->setFillColor(Color(rand() % 255, rand() % 255, rand() % 255));
        circle->setOrigin(Vector2f(radius, radius));
        circle->setOutlineThickness(5);
        circle->setOutlineColor(Color(rand() % 255, rand() % 255, rand() % 255));
        circle->setPosition(x, y);
        return circle;
    }

    RectangleShape* makeRectangle(Vector2f vect, float x, float y){
        RectangleShape* rectangle = new RectangleShape();
        rectangle->setSize(vect);
        rectangle->setFillColor(Color(rand() % 255, rand() % 255, rand() % 255));
        rectangle->setOutlineThickness(5);
        rectangle->setOutlineColor(Color(rand() % 255, rand() % 255, rand() % 255));
        rectangle->setOrigin(Vector2f(0.5 * vect.x, 0.5 * vect.y));
        rectangle->setPosition(x,y);
        rectangle->setRotation(rand() % 360);
        return rectangle;
    }

    CircleShape* makePolygon (float radius, size_t numSide, float x, float y){
        CircleShape* polygon = new CircleShape(radius, numSide);
        polygon->setFillColor(Color(rand() % 255, rand() % 255, rand() % 255));
        polygon->setOutlineThickness(5);
        polygon->setOutlineColor(Color(rand() % 255, rand() % 255, rand() % 255));
        polygon->setOrigin(Vector2f(radius, radius));
        polygon->setPosition(x, y);
        polygon->setRotation(rand() % 360);
        return polygon;
    }

};
