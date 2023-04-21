#include "Labirinto.h"
#include "Coordenada.h"

#include <stdio.h>
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include <array> 

void Labirinto::setNome_arquivo(const char *nome){
    this->nome_arquivo = nome;
}


void Labirinto::exibir_labirinto(){
    al_clear_to_color(al_map_rgb(0,0,0)); //Cor de background da tela
   mapa_desenho = al_load_bitmap("./imagenstrab/bloco.png");
    for(Coordenada& coordenada : coordenadas_tijolo){
        al_draw_bitmap(mapa_desenho,TAM_LADO*coordenada.getX(),TAM_LADO*coordenada.getY(),0);
    }

    

}

void Labirinto::carregarPosicaoDosTijolos(){
    int x, y;
    FILE* arquivoDoLabirinto = fopen(this->nome_arquivo, "r");
    if(arquivoDoLabirinto == NULL){
        printf("Erro em abrir o arquivo de posição dos tijolos!");
        exit(1);
    }
    int i = 0;
    while (fscanf(arquivoDoLabirinto, "%d %d", &x, &y) == 2){
        coordenadas_tijolo.addCoordenada(Coordenada(x,y));
        matriz_colisao[x][y]= TIJOLO;
        i++;
        
    }
    fclose(arquivoDoLabirinto);
}


void Labirinto::exibir_pilulas(){
    pilula_desenho = al_load_bitmap("./imagenstrab/sprite_pilula.png");
    for(Coordenada& coordenada : coordenadas_pilulas){
        al_draw_bitmap_region(pilula_desenho, TAM_LADO*(int)frame, 0, TAM_LADO, TAM_LADO, coordenada.getX() ,coordenada.getY(),0);
        //al_draw_bitmap(pilula_desenho,TAM_LADO*coordenada.getX(),TAM_LADO*coordenada.getY(),0);
    }
    
}
void Labirinto::carregarPosicaoDasPilulas(){
    for(int i = 0; i< ORDEM ; i++){
        for(int j = 0; j<ORDEM ; j++){
            if(matriz_colisao == CELULA_VAZIA){
                coordenadas_pilulas.addCoordenada(Coordenada(i,j));
                matriz_colisao[i][j]= PILULA; 
            }
        }
    }
}

void Labirinto::altera_frame_pilula(){
      frame += 0.2f;
      if(frame > 5){
         frame -= 5;
      }
}

void Labirinto::render(){
}

Labirinto::Labirinto(){
    for(int i = 0; i < ORDEM; i++){
        for(int j=0; j < ORDEM; j++){
            matriz_colisao[i][j] = CELULA_VAZIA;
        }
    }
}


