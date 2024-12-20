#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    float x, y;
    float target_x, target_y; 
    bool moving;                // Verifica se o jogador está se movendo
    float speed;

    Player(float init_x, float init_y);
    void move_to(float target_x, float target_y);
    void move();
    void draw() const;
};

#endif
