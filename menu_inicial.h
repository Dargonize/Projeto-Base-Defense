#ifndef MENU_INICIAL_H
#define MENU_INICIAL_H

#include <allegro5/allegro_font.h>

enum Dificuldade {
    FACIL = 60,    // 1 minuto
    MEDIO = 180,   // 3 minutos
    DIFICIL = 300  // 5 minutos
};

class MenuInicial {
public:
    MenuInicial();
    void desenhar(ALLEGRO_FONT* fonte) const;
    Dificuldade verificarSelecao(float mouse_x, float mouse_y, bool mouse_clicado);
    bool foiSelecionado() const { return dificuldade_selecionada; }
    Dificuldade getDificuldade() const { return dificuldade; }

private:
    float botao_x;
    float botao_y;
    float botao_largura;
    float botao_altura;
    float espaco_entre_botoes;
    bool dificuldade_selecionada;
    Dificuldade dificuldade;
};

#endif