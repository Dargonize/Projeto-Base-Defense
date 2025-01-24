#ifndef PROJETIL_H
#define PROJETIL_H

class Projetil {
public:
    float x, y;
    float dx, dy;
    float velocidade;
    float distancia_maxima;
    float distancia_percorrida;
    bool ativo;

    Projetil(float x_inicial, float y_inicial, float x_alvo, float y_alvo, bool eh_jogador = false);
    void atualizar();
    void desenhar() const;
    bool foraDeAlcance() const;
};

#endif