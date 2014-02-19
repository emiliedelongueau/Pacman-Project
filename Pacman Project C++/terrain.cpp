#include "terrain.h"

terrain::terrain(int L1, int C1)  {
	L = L1; //nbre de lignes
	C = C1; //nbre de colonnes
	t = new int[L*C];
}
terrain::~terrain() {
	if (L!=0 || C!=0) 
		{
			delete[] t;
	}
}

terrain::terrain() {
	L=0;
	C=0;
}

bool terrain::rempliTerrain(string nom) { //remplit le tableau du terrain en lisant un fichier
	ifstream FD(nom.c_str());
	if (!FD.is_open()) {
		cout << "help!" << endl;
		return false;
	} 
	
	for (int i = 0; i<L; i++) {
		for (int j = 0; j<C; j++) {
			FD >> t[j+C*i] ;
		}
	}

	FD.close();

	return true;
}

void terrain::afficheTerrain(NativeBitmap rien, NativeBitmap gomme, NativeBitmap vitamine, NativeBitmap mur, NativeBitmap porte, NativeBitmap maison, int nb_w, int nb_h) {

	for (int i=0;i<L;i++) {
		for (int j =0; j<C; j++) {
			
			switch (t[j+C*i]) {
				case 0 :
					putNativeBitmap(nb_w*j, nb_h*i, rien);
					break;

				case 1 :
					putNativeBitmap(nb_w*j, nb_h*i, gomme);
					break;

				case 2 :
					putNativeBitmap(nb_w*j, nb_h*i, vitamine);
					break;

				case 3 : 
					putNativeBitmap(nb_w*j, nb_h*i, mur);
					break;

				case 4 :
					putNativeBitmap(nb_w*j, nb_h*i, porte); 
					break;

				case 5 : 
					putNativeBitmap(nb_w*j, nb_h*i, maison);
					break;

			}
			
		}
	}
}





