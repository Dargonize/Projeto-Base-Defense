#ifndef ESTADO_JOGO_H
#define ESTADO_JOGO_H

#include "jogador.h"
#include "inimigo.h"
#include "base.h"
#include "projetil.h"
#include "caixa_municao.h"
#include "pacote_vida.h"
#include "lista_encadeada.h"
#include "gerenciador_som.h"
#include "menu_inicial.h"

const int LARGURA_TELA = 1920;
const int ALTURA_TELA = 1080;

class EstadoJogo {
private:
    Jogador jogador;
    Base base;
    ListaEncadeada<Inimigo> inimigos;
    ListaEncadeada<Projetil> projeteis_jogador;
    ListaEncadeada<Projetil> projeteis_inimigo;
    ListaEncadeada<CaixaMunicao> caixas_municao;
    ListaEncadeada<PacoteVida> pacotes_vida;
    
    GerenciadorSom som;
    
    float tempo_spawn_inimigo;
    float tempo_jogo;
    float tempo_dificuldade;
    float taxa_spawn;
    bool pausado;
    int inimigos_abatidos;
    float tempo_vitoria;
    
    bool verificarColisao(float x1, float y1, float r1, float x2, float y2, float r2);
    bool verificarColisaoBase(float x_inimigo, float y_inimigo);
    void gerarInimigo();
    void atualizarProjeteis();
    void verificarColisoes();
    void removerEntidadesMortas();
    void atualizarDificuldade();

public:
    EstadoJogo(Dificuldade dif);
    ~EstadoJogo();
    void atualizar(ALLEGRO_KEYBOARD_STATE* teclas, float mouse_x, float mouse_y);
    void desenhar() const;
    bool jogoAcabou() const;
    bool vitoria() const;
    void alternarPause();
    bool estaPausado() const { return pausado; }
    Jogador& getJogador() { return jogador; }
    Base& getBase() { return base; }
    GerenciadorSom& getSom() { return som; }
    int getInimigosAbatidos() const { return inimigos_abatidos; }
};

#endif