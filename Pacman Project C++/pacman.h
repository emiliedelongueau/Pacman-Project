#pragma once
#include "terrain.h"
#include "utils.h"


struct pacman {
	int i,j;
	Direction dir;
	Direction tmpDir;

	int etat;// 0,1 ou 2,pour differencier les images du pacman a afficher(debut, normal ou mangevitamine)
	bool gomme;//si true, on incrementera le score 
	bool changeDir;//teste si pacman a pu tourner dans la direction voulue (si pas de mur)


	pacman();//constructeur
	pacman(int x, int y);
	~pacman();

	void avance(terrain& T,NativeBitmap rien, NativeBitmap pacman_debut, NativeBitmap pacman_normal, NativeBitmap pacman_vitamine, int nb_w, int nb_h);
	void tourne(Direction dir1);
	void affiche(NativeBitmap pacman_debut, NativeBitmap pacman_normal, NativeBitmap pacman_vitamine, int nb_w, int nb_h);
};

