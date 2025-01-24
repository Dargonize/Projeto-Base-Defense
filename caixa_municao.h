#ifndef CAIXA_MUNICAO_H
#define CAIXA_MUNICAO_H

class CaixaMunicao {
public:
    float x, y;
    int quantidade;
    float tempo_vida;
    bool ativo;
    
    CaixaMunicao(float pos_x, float pos_y);
    void atualizar();
    void desenhar() const;
    bool estaExpirada() const;
};

#endif