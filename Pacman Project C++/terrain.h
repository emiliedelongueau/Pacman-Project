#pragma once
#include <fstream> 
using namespace std;
#include <iostream>
using namespace std;
#include <sstream>
#include <Imagine/Graphics.h>
using namespace Imagine;
#include <Imagine/Images.h>
using namespace std;



class terrain {

public :
	
	int* t;
	int L,C;
	
	inline int& operator() (int i, int j) {
		return t[j+C*i];
	}
	inline int operator() (int i, int j) const {
		return t[j+C*i];
	} 

	terrain();
	terrain(int L1, int C1);
	~terrain();

	bool rempliTerrain(string nom);//remplit le tableau du terrain grace a un fichier
	void afficheTerrain(NativeBitmap rien, NativeBitmap gomme, NativeBitmap vitamine, NativeBitmap mur, NativeBitmap porte, NativeBitmap maison, int nb_w, int nb_h);
};




