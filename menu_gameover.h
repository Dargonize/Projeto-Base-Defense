#ifndef MENU_GAMEOVER_H
#define MENU_GAMEOVER_H

#include <allegro5/allegro_font.h>

enum GameOverReason {
    VITORIA,
    BASE_DESTRUIDA,
    JOGADOR_MORTO
};

class MenuGameOver {
public:
    MenuGameOver(GameOverReason reason, int inimigos_abatidos);
    void desenhar(ALLEGRO_FONT* fonte) const;
    bool jogarNovamente(float mouse_x, float mouse_y, bool mouse_clicado) const;
private:
    GameOverReason reason;
    int inimigos_abatidos;
    float botao_x;
    float botao_y;
    float botao_largura;
    float botao_altura;
};

#endif