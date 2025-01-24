#include "estado_jogo.h"
#include <allegro5/allegro_font.h>
#include <cstdlib>
#include <cmath>

extern ALLEGRO_FONT* fonte;

EstadoJogo::EstadoJogo(Dificuldade dif)
    : jogador(LARGURA_TELA / 2, ALTURA_TELA / 2, som),
      base(LARGURA_TELA / 2, ALTURA_TELA / 2),
      tempo_spawn_inimigo(0),
      tempo_jogo(0),
      tempo_dificuldade(0),
      taxa_spawn(3.0f),
      pausado(false),
      inimigos_abatidos(0),
      tempo_vitoria(static_cast<float>(dif)) {
    som.iniciarMusicaFundo();
}

EstadoJogo::~EstadoJogo() {
    som.pararMusicaFundo();
}

void EstadoJogo::alternarPause() {
    pausado = !pausado;
    if (pausado) {
        som.pararMusicaFundo();
    } else {
        som.iniciarMusicaFundo();
    }
}

bool EstadoJogo::verificarColisao(float x1, float y1, float r1, float x2, float y2, float r2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float distancia = sqrt(dx * dx + dy * dy);
    return distancia < (r1 + r2);
}

bool EstadoJogo::verificarColisaoBase(float x_inimigo, float y_inimigo) {
    
    float dx = x_inimigo - base.x;
    float dy = y_inimigo - base.y;
    float distancia = sqrt(dx * dx + dy * dy);
    
   
    return distancia <= (base.raio + 15);
}

void EstadoJogo::gerarInimigo() {
    float x, y;
    int lado = rand() % 4;
    
    switch (lado) {
        case 0: 
            x = rand() % LARGURA_TELA;
            y = -20;
            break;
        case 1: 
            x = LARGURA_TELA + 20;
            y = rand() % ALTURA_TELA;
            break;
        case 2:
            x = rand() % LARGURA_TELA;
            y = ALTURA_TELA + 20;
            break;
        case 3: 
            x = -20;
            y = rand() % ALTURA_TELA;
            break;
    }
    
    inimigos.inserir_inicio(Inimigo(x, y));
}

void EstadoJogo::atualizarProjeteis() {
    for (No<Projetil>* no = projeteis_jogador.começo(); no != nullptr; no = no->proximo) {
        no->dados.atualizar();
    }
    
    for (No<Projetil>* no = projeteis_inimigo.começo(); no != nullptr; no = no->proximo) {
        no->dados.atualizar();
    }
}

void EstadoJogo::verificarColisoes() {
   
    for (No<Projetil>* proj = projeteis_jogador.começo(); proj != nullptr; proj = proj->proximo) {
        if (!proj->dados.ativo) continue;
        
        for (No<Inimigo>* inim = inimigos.começo(); inim != nullptr; inim = inim->proximo) {
            if (!inim->dados.ativo) continue;
            
            if (verificarColisao(proj->dados.x, proj->dados.y, 5,
                               inim->dados.x, inim->dados.y, 15)) {
                proj->dados.ativo = false;
                inim->dados.receberDano(25);
                som.tocarSom(som.som_dano, 0.5);
                
                if (inim->dados.estaMorto()) {
                    inimigos_abatidos++;
                    if (rand() % 100 < 30) { 
                        caixas_municao.inserir_inicio(CaixaMunicao(inim->dados.x, inim->dados.y));
                    }
                    if (rand() % 100 < 10) { 
                        pacotes_vida.inserir_inicio(PacoteVida(inim->dados.x, inim->dados.y));
                    }
                }
            }
        }
    }
    
    
    for (No<Projetil>* proj = projeteis_inimigo.começo(); proj != nullptr; proj = proj->proximo) {
        if (!proj->dados.ativo) continue;
        
        if (verificarColisao(proj->dados.x, proj->dados.y, 5,
                           jogador.x, jogador.y, 15)) {
            proj->dados.ativo = false;
            jogador.receberDano(10);
            som.tocarSom(som.som_dano, 0.5);
        }
        
        if (verificarColisao(proj->dados.x, proj->dados.y, 5,
                           base.x, base.y, base.raio)) {
            proj->dados.ativo = false;
            base.receberDano(3);
            som.tocarSom(som.som_dano, 0.5);
        }
    }

    
    for (No<Inimigo>* inim = inimigos.começo(); inim != nullptr; inim = inim->proximo) {
        if (!inim->dados.ativo) continue;

        if (verificarColisaoBase(inim->dados.x, inim->dados.y)) {
            inim->dados.vida = 0;
            base.receberDano(10);
            som.tocarSom(som.som_dano, 1.0);
            inimigos_abatidos++;
        }
    }
    
    
    for (No<CaixaMunicao>* caixa = caixas_municao.começo(); caixa != nullptr; caixa = caixa->proximo) {
        if (!caixa->dados.ativo) continue;
        
        if (verificarColisao(jogador.x, jogador.y, 15,
                           caixa->dados.x, caixa->dados.y, 10)) {
            jogador.coletarMunicao(caixa->dados.quantidade);
            caixa->dados.ativo = false;
            som.tocarSom(som.som_municao, 0.7);
        }
    }

    
    for (No<PacoteVida>* pacote = pacotes_vida.começo(); pacote != nullptr; pacote = pacote->proximo) {
        if (!pacote->dados.ativo) continue;
        
        if (verificarColisao(jogador.x, jogador.y, 15,
                           pacote->dados.x, pacote->dados.y, 10)) {
            pacote->dados.ativo = false;
            jogador.curar(25);
            som.tocarSom(som.som_vida, 0.7);
        }
    }
}

void EstadoJogo::removerEntidadesMortas() {
    
    No<Projetil>* proj = projeteis_jogador.começo();
    while (proj != nullptr) {
        No<Projetil>* proximo = proj->proximo;
        if (proj->dados.foraDeAlcance()) {
            projeteis_jogador.remover(proj);
        }
        proj = proximo;
    }
    
    proj = projeteis_inimigo.começo();
    while (proj != nullptr) {
        No<Projetil>* proximo = proj->proximo;
        if (proj->dados.foraDeAlcance()) {
            projeteis_inimigo.remover(proj);
        }
        proj = proximo;
    }
    
    
    No<Inimigo>* inim = inimigos.começo();
    while (inim != nullptr) {
        No<Inimigo>* proximo = inim->proximo;
        if (inim->dados.estaMorto()) {
            inimigos.remover(inim);
        }
        inim = proximo;
    }
    
   
    No<CaixaMunicao>* caixa = caixas_municao.começo();
    while (caixa != nullptr) {
        No<CaixaMunicao>* proximo = caixa->proximo;
        if (caixa->dados.estaExpirada()) {
            caixas_municao.remover(caixa);
        }
        caixa = proximo;
    }

   
    No<PacoteVida>* pacote = pacotes_vida.começo();
    while (pacote != nullptr) {
        No<PacoteVida>* proximo = pacote->proximo;
        if (pacote->dados.estaExpirado()) {
            pacotes_vida.remover(pacote);
        }
        pacote = proximo;
    }
}

void EstadoJogo::atualizarDificuldade() {
    tempo_dificuldade += 1.0f / 60.0f;
    if (tempo_dificuldade >= 30.0f) {
        taxa_spawn *= 0.9f;
        tempo_dificuldade = 0;
    }
}

void EstadoJogo::atualizar(ALLEGRO_KEYBOARD_STATE* teclas, float mouse_x, float mouse_y) {
    if (pausado) return;

    tempo_jogo += 1.0f / 60.0f;
    
    
    tempo_spawn_inimigo += 1.0f / 60.0f;
    if (tempo_spawn_inimigo >= taxa_spawn) {
        gerarInimigo();
        tempo_spawn_inimigo = 0;
    }
    
   
    jogador.atualizar(teclas, projeteis_jogador, mouse_x, mouse_y);
    base.atualizar();
    
    for (No<Inimigo>* inim = inimigos.começo(); inim != nullptr; inim = inim->proximo) {
        inim->dados.atualizar(jogador.x, jogador.y, projeteis_inimigo);
    }
    
    for (No<CaixaMunicao>* caixa = caixas_municao.começo(); caixa != nullptr; caixa = caixa->proximo) {
        caixa->dados.atualizar();
    }

    for (No<PacoteVida>* pacote = pacotes_vida.começo(); pacote != nullptr; pacote = pacote->proximo) {
        pacote->dados.atualizar();
    }
    
    atualizarProjeteis();
    verificarColisoes();
    removerEntidadesMortas();
    atualizarDificuldade();
}

void EstadoJogo::desenhar() const {
    base.desenhar();
    
    for (const No<Projetil>* proj = projeteis_jogador.começo(); proj != nullptr; proj = proj->proximo) {
        proj->dados.desenhar();
    }
    for (const No<Projetil>* proj = projeteis_inimigo.começo(); proj != nullptr; proj = proj->proximo) {
        proj->dados.desenhar();
    }
    
    for (const No<Inimigo>* inim = inimigos.começo(); inim != nullptr; inim = inim->proximo) {
        inim->dados.desenhar();
    }
    
    for (const No<CaixaMunicao>* caixa = caixas_municao.começo(); caixa != nullptr; caixa = caixa->proximo) {
        caixa->dados.desenhar();
    }

    for (const No<PacoteVida>* pacote = pacotes_vida.começo(); pacote != nullptr; pacote = pacote->proximo) {
        pacote->dados.desenhar();
    }
    
    jogador.desenhar();

    
    al_draw_textf(fonte, al_map_rgb(255, 255, 255),
                 LARGURA_TELA - 10, 10, ALLEGRO_ALIGN_RIGHT,
                 "Vida da Base: %d/%d", base.vida, base.vida_maxima);

    float tempo_restante = tempo_vitoria - tempo_jogo;
    int minutos = (int)tempo_restante / 60;
    int segundos = (int)tempo_restante % 60;
    al_draw_textf(fonte, al_map_rgb(255, 255, 255),
                 LARGURA_TELA - 10, 40, ALLEGRO_ALIGN_RIGHT,
                 "Tempo: %02d:%02d", minutos, segundos);
}

bool EstadoJogo::jogoAcabou() const {
    return jogador.estaMorto() || base.estaDestruida();
}

bool EstadoJogo::vitoria() const {
    return tempo_jogo >= tempo_vitoria;
}
