#include "pacote_vida.h"
#include <allegro5/allegro_primitives.h>

PacoteVida::PacoteVida(float pos_x, float pos_y) 
    : x(pos_x), y(pos_y), tempo_vida(5.0f), ativo(true) {
}

void PacoteVida::atualizar() {
    if (!ativo) return;
    
    tempo_vida -= 1.0f / 60.0f;
    if (tempo_vida <= 0) {
        ativo = false;
    }
}

void PacoteVida::desenhar() const {
    if (!ativo) return;
    al_draw_filled_circle(x, y, 10, al_map_rgb(255, 0, 0));
    float porcentagem_vida = tempo_vida / 5.0f;
    al_draw_arc(x, y, 12, 0, porcentagem_vida * 2 * ALLEGRO_PI, 
                al_map_rgb(255, 0, 0), 2);
}

bool PacoteVida::estaExpirado() const {
    return !ativo || tempo_vida <= 0;
}