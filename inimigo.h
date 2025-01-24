#ifndef INIMIGO_H
#define INIMIGO_H

#include "projetil.h"
#include "lista_encadeada.h"

class Inimigo {
public:
    float x, y;
    float velocidade;
    int vida;
    float recarga_tiro;
    float tempo_recarga;
    bool ativo;

    Inimigo(float x_inicial, float y_inicial);
    void mover(float x_alvo, float y_alvo);
    void desenhar() const;
    void atirar(float x_alvo, float y_alvo, ListaEncadeada<Projetil>& projeteis);
    void receberDano(int quantidade);
    bool estaMorto() const;
    void atualizar(float x_jogador, float y_jogador, ListaEncadeada<Projetil>& projeteis);
};

#endif