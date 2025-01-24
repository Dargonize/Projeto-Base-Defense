#ifndef PACOTE_VIDA_H
#define PACOTE_VIDA_H

class PacoteVida {
public:
    float x, y;
    float tempo_vida;
    bool ativo;
    
    PacoteVida(float pos_x, float pos_y);
    void atualizar();
    void desenhar() const;
    bool estaExpirado() const;
};

#endif