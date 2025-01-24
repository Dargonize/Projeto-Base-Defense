#ifndef GERENCIADOR_SOM_H
#define GERENCIADOR_SOM_H

#include <allegro5/allegro_audio.h>

class GerenciadorSom {
public:
    ALLEGRO_SAMPLE* som_tiro;
    ALLEGRO_SAMPLE* som_dano;
    ALLEGRO_SAMPLE* som_vida;
    ALLEGRO_SAMPLE* som_municao;
    ALLEGRO_SAMPLE* musica_fundo;
    ALLEGRO_SAMPLE_INSTANCE* musica_instance;

    GerenciadorSom();
    ~GerenciadorSom();
    void tocarSom(ALLEGRO_SAMPLE* som, float volume = 1.0);
    void iniciarMusicaFundo();
    void pararMusicaFundo();
};

#endif