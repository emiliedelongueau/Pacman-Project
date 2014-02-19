#pragma once
#include "terrain.h"
#include "utils.h"
#include "pacman.h"


struct fantome {
	int i,j;
	Direction dir;

	int tmp; //garde en memoire ce que contient la case sur laquelle il est (rien, gomme, vitamine) pour reafficher l'image apres son passage
	int etat; // 6(normal),7(vitamine),8(mort)
	int compteurDebut;
	fantome();
	~fantome();

	void initialise(int x, int y,int etat_ini,int tmp_ini,Direction dir_ini);
	void tourne(Direction dir1);
	void affiche(NativeBitmap fantome_normal, NativeBitmap fantome_vitamine, int nb_w, int nb_h);
	void afficheTmp(NativeBitmap rien, NativeBitmap gomme, NativeBitmap vitamine, NativeBitmap maison, NativeBitmap porte, int nb_w, int nb_h); //reaffiche l'image de la case apres passage du fantome
	void avance(terrain& T,NativeBitmap rien, NativeBitmap gomme, NativeBitmap vitamine, NativeBitmap maison, NativeBitmap porte, NativeBitmap fantome_normal, NativeBitmap fantome_vitamine, int nb_w, int nb_h);
	void choisirDir(pacman P, terrain& T);// fantome suit pacman
	void fuirDir(pacman P, terrain& T);// fantome fuit pacman
	bool mangepacman(pacman& P); //teste si fantome a mange pacman
	bool meurt(pacman& P); // teste si fantome est mange par pacman
};



