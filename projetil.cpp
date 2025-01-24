#include "projetil.h"
#include <allegro5/allegro_primitives.h>
#include <cmath>

Projetil::Projetil(float x_inicial, float y_inicial, float x_alvo, float y_alvo, bool eh_jogador) 
    : x(x_inicial), y(y_inicial), velocidade(8.0f), 
      distancia_maxima(eh_jogador ? 1200.0f : 400.0f), 
      distancia_percorrida(0.0f), ativo(true) {
    float angulo = atan2(y_alvo - y_inicial, x_alvo - x_inicial);
    dx = cos(angulo) * velocidade;
    dy = sin(angulo) * velocidade;
}

void Projetil::atualizar() {
    if (!ativo) return;
    
    x += dx;
    y += dy;
    
    float dist = sqrt(dx * dx + dy * dy);
    distancia_percorrida += dist;
    
    if (distancia_percorrida >= distancia_maxima) {
        ativo = false;
    }
}

void Projetil::desenhar() const {
    if (!ativo) return;
    al_draw_filled_circle(x, y, 5, al_map_rgb(255, 255, 0));
}

bool Projetil::foraDeAlcance() const {
    return !ativo || distancia_percorrida >= distancia_maxima;
}