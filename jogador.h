#ifndef JOGADOR_H
#define JOGADOR_H

#include "projetil.h"
#include "lista_encadeada.h"
#include "gerenciador_som.h"
#include <allegro5/allegro.h>

class Jogador {
public:
    float x, y;
    float x_alvo, y_alvo;
    bool movendo;
    float velocidade;
    int vida;
    int municao;
    float recarga_tiro;
    float tempo_recarga;

private:
    GerenciadorSom& som;

public:
    Jogador(float x_inicial, float y_inicial, GerenciadorSom& gerenciador_som);
    void definirDestino(float x, float y);
    void mover_para(float x_alvo, float y_alvo);
    void mover();
    void desenhar() const;
    void atirar(float x_alvo, float y_alvo, ListaEncadeada<Projetil>& projeteis);
    void coletarMunicao(int quantidade);
    void receberDano(int quantidade);
    bool estaMorto() const;
    void atualizar(ALLEGRO_KEYBOARD_STATE* teclas, ListaEncadeada<Projetil>& projeteis, float mouse_x, float mouse_y);
    void curar(int quantidade);
};

#endif