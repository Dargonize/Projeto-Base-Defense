#include "inimigo.h"
#include <allegro5/allegro_primitives.h>
#include <cmath>

Inimigo::Inimigo(float x_inicial, float y_inicial) 
    : x(x_inicial), y(y_inicial), velocidade(2.0f), vida(50),
      recarga_tiro(0.5f), tempo_recarga(0.0f), ativo(true) {}

void Inimigo::mover(float x_alvo, float y_alvo) {
    if (!ativo) return;
    
    float dx = x_alvo - x;
    float dy = y_alvo - y;
    float distancia = std::sqrt(dx * dx + dy * dy);
    
    if (distancia <= velocidade) return;

    float dx_normalizado = dx / distancia;
    float dy_normalizado = dy / distancia;
    
    x += dx_normalizado * velocidade;
    y += dy_normalizado * velocidade;
}

void Inimigo::atirar(float x_alvo, float y_alvo, ListaEncadeada<Projetil>& projeteis) {
    if (tempo_recarga > 0) return;
    
    projeteis.inserir_inicio(Projetil(x, y, x_alvo, y_alvo, false)); 
    tempo_recarga = recarga_tiro;
}

void Inimigo::receberDano(int quantidade) {
    vida -= quantidade;
    if (vida < 0) vida = 0;
}

bool Inimigo::estaMorto() const {
    return vida <= 0 || !ativo;
}

void Inimigo::atualizar(float x_jogador, float y_jogador, ListaEncadeada<Projetil>& projeteis) {
    if (!ativo) return;
    
    mover(x_jogador, y_jogador);
    
    atirar(x_jogador, y_jogador, projeteis);
    
    if (tempo_recarga > 0) {
        tempo_recarga -= 1.0f / 60.0f;
    }
}

void Inimigo::desenhar() const {
    if (!ativo) return;
    
    al_draw_filled_rectangle(x - 15, y - 15, x + 15, y + 15, al_map_rgb(255, 0, 0));
    
    float porcentagem_vida = (float)vida / 50.0f;
    al_draw_filled_rectangle(x - 15, y - 25, x - 15 + (30 * porcentagem_vida), y - 20, 
                           al_map_rgb(255 * (1 - porcentagem_vida), 255 * porcentagem_vida, 0));
}
