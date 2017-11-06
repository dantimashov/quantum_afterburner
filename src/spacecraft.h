#pragma once
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cmath>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;
const int MAX_Y = 600;
const int MAX_X = 800;
const double ANGLE = 3.14/36;

struct coord {
    float x;
    float y;
};

struct spaceCraft {
    spaceCraft()
            : radius(100)
            , d_vel(2)
            , ship_size(20)
            , undefined(200)
            , velocity(3)
            , lives(5)
            , fuel(0)
    {
        direction.x = 0;
        direction.y = -1;
        position.x = MAX_X / 2;
        position.y = MAX_Y / 2;
    };

    ~spaceCraft() {}

    void flight(short keyPress) {
        switch (keyPress) {
            case 77: {
                coord oldDir = direction;
                direction.x = oldDir.x * cos(ANGLE) - oldDir.y * sin(ANGLE);
                direction.y = oldDir.x * sin(ANGLE) + oldDir.y * cos(ANGLE);
                break;
            };
            case 75: {
                coord oldDir = direction;
                direction.x = oldDir.x * cos(ANGLE) + oldDir.y * sin(ANGLE);
                direction.y = -oldDir.x * sin(ANGLE) + oldDir.y * cos(ANGLE);
                break;
            };
            case 73: {
                if (fuel > 0) {
                    fuel -= 0.03;
                    velocity += 0.06;
                    if (velocity > 9)
                        velocity = 9;
                    break;
                } else {
                    fuel = 0;
                    break;
                };
            };
            case 80: {
                if (fuel > 0) {
                    fuel -= 0.03;
                    velocity -= 0.06;
                    if (velocity < 3)
                        velocity = 3;
                    break;
                } else {
                    fuel = 0;
                    break;
                };
            };
        };
    };

    coord getPosition() {
        return position;
    };

    void getInTouch() {
        lives--;
    };

    void getBonus(int bonusType) {
        switch (bonusType) {
            case 1: {
                lives++;
                break;
            };
            case 2: {
                radius = radius - 60;
                if (radius < 30)
                    radius = 30;
                d_vel = undefined / radius;
                break;
            };
            case 3: {
                d_vel -= 2;
                if (d_vel < 1)
                    d_vel = 1;
                radius = undefined / d_vel;
                break;
            };
            case 4: {
                fuel += 4;
                if (fuel > 10)
                    fuel = 10;
                break;
            };
        };
    }

    void teleportation() {
        srand(time(NULL) * (rand() % 100) * (rand() % 100));
        float dx = 2 * radius * (static_cast<float> (rand() % 100) / 100) - radius;
        float dy = 2 * radius * ( static_cast<float> (rand() % 100) / 100) - radius;
        position.x += dx;
        position.y += dy;
        d_vel = undefined / radius;
        velocity = 3 + rand() % (static_cast<int>(d_vel) + 1);
    };

    int getVelocity() {
        return velocity;
    };

    coord getDirection() {
        return direction;
    };

    void setPosition(float x, float y) {
        position.x = x;
        position.y = y;
    };

    float             radius;
    float             d_vel;
    float             ship_size;
    const int         undefined;
    float             velocity;
    coord             direction;
    coord             position;
    int               lives;
    float             fuel;
};