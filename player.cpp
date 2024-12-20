#include "player.h"
#include <allegro5/allegro_primitives.h>
#include <cmath>

Player::Player(float init_x, float init_y) 
    : x(init_x), y(init_y), target_x(init_x), target_y(init_y), moving(false), speed(4.0f) {}

void Player::move_to(float target_x, float target_y) {
    this->target_x = target_x;
    this->target_y = target_y;
    moving = true;
}

void Player::move() {
    if (!moving) return;

    float dx = target_x - x;
    float dy = target_y - y;
    float distance = std::sqrt(dx * dx + dy * dy);
    
    if (distance <= speed) {
        x = target_x;
        y = target_y;
        moving = false;
        return;
    }

    float normalized_dx = dx / distance;
    float normalized_dy = dy / distance;
    
    x += normalized_dx * speed;
    y += normalized_dy * speed;
}

void Player::draw() const {
    al_draw_filled_rectangle(x - 25, y - 25, x + 25, y + 25, al_map_rgb(0, 255, 0));
}
