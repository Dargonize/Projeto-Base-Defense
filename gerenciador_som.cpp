#include "gerenciador_som.h"
#include <iostream>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

GerenciadorSom::GerenciadorSom() {
    som_tiro = al_load_sample("tiro.wav");
    som_dano = al_load_sample("dano.wav");
    som_vida = al_load_sample("vida.wav");
    som_municao = al_load_sample("municao.wav");
    musica_fundo = al_load_sample("musica.wav");
    
    if (!som_tiro) std::cerr << "Falha ao carregar som de tiro!" << std::endl;
    if (!som_dano) std::cerr << "Falha ao carregar som de dano!" << std::endl;
    if (!som_vida) std::cerr << "Falha ao carregar som de vida!" << std::endl;
    if (!som_municao) std::cerr << "Falha ao carregar som de munição!" << std::endl;
    if (!musica_fundo) std::cerr << "Falha ao carregar música de fundo!" << std::endl;

    if (musica_fundo) {
        musica_instance = al_create_sample_instance(musica_fundo);
        al_set_sample_instance_playmode(musica_instance, ALLEGRO_PLAYMODE_LOOP);
        al_attach_sample_instance_to_mixer(musica_instance, al_get_default_mixer());
    }
}

GerenciadorSom::~GerenciadorSom() {
    if (som_tiro) al_destroy_sample(som_tiro);
    if (som_dano) al_destroy_sample(som_dano);
    if (som_vida) al_destroy_sample(som_vida);
    if (som_municao) al_destroy_sample(som_municao);
    if (musica_instance) al_destroy_sample_instance(musica_instance);
    if (musica_fundo) al_destroy_sample(musica_fundo);
}

void GerenciadorSom::tocarSom(ALLEGRO_SAMPLE* som, float volume) {
    if (som) {
        al_play_sample(som, volume, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, nullptr);
    }
}

void GerenciadorSom::iniciarMusicaFundo() {
    if (musica_instance) {
        al_set_sample_instance_gain(musica_instance, 0.5); // Ajuste o volume conforme necessário
        al_play_sample_instance(musica_instance);
    }
}

void GerenciadorSom::pararMusicaFundo() {
    if (musica_instance) {
        al_stop_sample_instance(musica_instance);
    }
}