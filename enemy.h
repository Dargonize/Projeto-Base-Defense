#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
public:
    float x, y;
    float speed;

    Enemy(float init_x, float init_y);
    void move(float target_x, float target_y);
    void draw() const;
};

#endif
