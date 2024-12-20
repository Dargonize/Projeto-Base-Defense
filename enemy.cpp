#include "enemy.h"
#include <allegro5/allegro_primitives.h>
#include <cmath>

Enemy::Enemy(float init_x, float init_y) 
    : x(init_x), y(init_y), speed(2.0f) {}

void Enemy::move(float target_x, float target_y) {
    float dx = target_x - x;
    float dy = target_y - y;
    float distance = std::sqrt(dx * dx + dy * dy);
    
    if (distance <= speed) return;

    float normalized_dx = dx / distance;
    float normalized_dy = dy / distance;
    
    x += normalized_dx * speed;
    y += normalized_dy * speed;
}

void Enemy::draw() const {
    al_draw_filled_rectangle(x - 25, y - 25, x + 25, y + 25, al_map_rgb(255, 0, 0));
}