#include "jogador.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <cmath>

extern ALLEGRO_FONT* fonte;

Jogador::Jogador(float x_inicial, float y_inicial, GerenciadorSom& gerenciador_som)
    : x(x_inicial), y(y_inicial), x_alvo(x_inicial), y_alvo(y_inicial), 
      movendo(false), velocidade(6.0f), vida(100), municao(50),
      recarga_tiro(0.25f), tempo_recarga(0.0f), som(gerenciador_som) {}

void Jogador::definirDestino(float x, float y) {
    x_alvo = x;
    y_alvo = y;
    movendo = true;
}

void Jogador::mover_para(float x_alvo, float y_alvo) {
    this->x_alvo = x_alvo;
    this->y_alvo = y_alvo;
    movendo = true;
}

void Jogador::mover() {
    if (!movendo) return;

    float dx = x_alvo - x;
    float dy = y_alvo - y;
    float distancia = std::sqrt(dx * dx + dy * dy);
    
    if (distancia <= velocidade) {
        x = x_alvo;
        y = y_alvo;
        movendo = false;
        return;
    }

    x += (dx / distancia) * velocidade;
    y += (dy / distancia) * velocidade;
}

void Jogador::atirar(float x_alvo, float y_alvo, ListaEncadeada<Projetil>& projeteis) {
    if (municao <= 0 || tempo_recarga > 0) return;
    
    projeteis.inserir_inicio(Projetil(x, y, x_alvo, y_alvo, true)); // Specify as player projectile
    municao--;
    tempo_recarga = recarga_tiro;
    
    som.tocarSom(som.som_tiro, 0.5);
}

void Jogador::coletarMunicao(int quantidade) {
    municao += quantidade;
}

void Jogador::receberDano(int quantidade) {
    vida -= quantidade;
    if (vida < 0) vida = 0;
}

bool Jogador::estaMorto() const {
    return vida <= 0;
}

void Jogador::atualizar(ALLEGRO_KEYBOARD_STATE* teclas, ListaEncadeada<Projetil>& projeteis, float mouse_x, float mouse_y) {
    if (tempo_recarga > 0) {
        tempo_recarga -= 1.0f / 60.0f;
    }
    mover();
    
    if (al_key_down(teclas, ALLEGRO_KEY_Q)) {
        atirar(mouse_x, mouse_y, projeteis);
    }
}

void Jogador::desenhar() const {
    al_draw_filled_rectangle(x - 15, y - 15, x + 15, y + 15, al_map_rgb(0, 255, 0));
    
    float porcentagem_vida = (float)vida / 100.0f;
    al_draw_filled_rectangle(x - 15, y - 25, x - 15 + (30 * porcentagem_vida), y - 20, 
                           al_map_rgb(255 * (1 - porcentagem_vida), 255 * porcentagem_vida, 0));
    
    al_draw_textf(fonte, al_map_rgb(255, 255, 255), x, y + 30, ALLEGRO_ALIGN_CENTRE, 
                 "Munição: %d", municao);
}

void Jogador::curar(int quantidade) {
    vida += quantidade;
    if (vida > 100) vida = 100;
}