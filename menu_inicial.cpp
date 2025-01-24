#include "menu_inicial.h"
#include <allegro5/allegro_primitives.h>
#include "estado_jogo.h"

MenuInicial::MenuInicial() : dificuldade_selecionada(false) {
    botao_largura = 200;
    botao_altura = 50;
    espaco_entre_botoes = 20;
    botao_x = LARGURA_TELA / 2 - botao_largura / 2;
    botao_y = ALTURA_TELA / 2;
}

void MenuInicial::desenhar(ALLEGRO_FONT* fonte) const {
    al_draw_text(fonte, al_map_rgb(255, 255, 255), 
                 LARGURA_TELA / 2, ALTURA_TELA / 3,
                 ALLEGRO_ALIGN_CENTER, "Base Defense");

    al_draw_text(fonte, al_map_rgb(255, 255, 255),
                 LARGURA_TELA / 2, ALTURA_TELA / 3 + 50,
                 ALLEGRO_ALIGN_CENTER, "Selecione a Dificuldade:");

    // Botão Fácil
    al_draw_filled_rectangle(botao_x, botao_y, botao_x + botao_largura, botao_y + botao_altura, 
                           al_map_rgb(0, 255, 0));
    al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, botao_y + 10,
                 ALLEGRO_ALIGN_CENTER, "Fácil (1 min)");

    // Botão Médio
    al_draw_filled_rectangle(botao_x, botao_y + botao_altura + espaco_entre_botoes, 
                           botao_x + botao_largura, botao_y + 2 * botao_altura + espaco_entre_botoes, 
                           al_map_rgb(255, 255, 0));
    al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, botao_y + botao_altura + espaco_entre_botoes + 10,
                 ALLEGRO_ALIGN_CENTER, "Médio (3 min)");

    // Botão Difícil
    al_draw_filled_rectangle(botao_x, botao_y + 2 * (botao_altura + espaco_entre_botoes), 
                           botao_x + botao_largura, botao_y + 3 * botao_altura + 2 * espaco_entre_botoes, 
                           al_map_rgb(255, 0, 0));
    al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2, botao_y + 2 * (botao_altura + espaco_entre_botoes) + 10,
                 ALLEGRO_ALIGN_CENTER, "Difícil (5 min)");
}

Dificuldade MenuInicial::verificarSelecao(float mouse_x, float mouse_y, bool mouse_clicado) {
    if (!mouse_clicado) return (Dificuldade)0;

    if (mouse_x >= botao_x && mouse_x <= botao_x + botao_largura) {
        // Botão Fácil
        if (mouse_y >= botao_y && mouse_y <= botao_y + botao_altura) {
            dificuldade = FACIL;
            dificuldade_selecionada = true;
            return FACIL;
        }
        // Botão Médio
        if (mouse_y >= botao_y + botao_altura + espaco_entre_botoes && 
            mouse_y <= botao_y + 2 * botao_altura + espaco_entre_botoes) {
            dificuldade = MEDIO;
            dificuldade_selecionada = true;
            return MEDIO;
        }
        // Botão Difícil
        if (mouse_y >= botao_y + 2 * (botao_altura + espaco_entre_botoes) && 
            mouse_y <= botao_y + 3 * botao_altura + 2 * espaco_entre_botoes) {
            dificuldade = DIFICIL;
            dificuldade_selecionada = true;
            return DIFICIL;
        }
    }

    return (Dificuldade)0;
}