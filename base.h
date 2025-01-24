#ifndef BASE_H
#define BASE_H

class Base
{
public:
    float x, y;
    int vida;
    int vida_maxima;
    float taxa_regeneracao;
    float tempo_regeneracao;
    float raio; 

    Base(float pos_x, float pos_y)
        : x(pos_x), y(pos_y), vida(100), vida_maxima(100),
          taxa_regeneracao(0.0f), tempo_regeneracao(0.0f),
          raio(240.0f) {} 

    void atualizar();
    void desenhar() const;
    void receberDano(int dano = 10);
    bool estaDestruida() const;
};

#endif