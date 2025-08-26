#include "canvas.hpp"

void init_canvas(Canvas* canvas, float w, float h, composedObject co, int nLigne, int nColonnes) {
  canvas -> width = w;
  canvas -> height = h;
  canvas -> co = co;
  canvas -> nLigne = nLigne;
  canvas -> nColonnes = nColonnes;
  canvas -> tabTransfGrille = new  elemTransf*[nLigne*nColonnes];
}

elemTransf ** init_tabTransfGrille(int nTransf, void initElemTransf(elemTransf*,float, float, int, int, int, float, string*, int),Canvas* canvas, string * tabColors, int nColors) {
// cette fonction remplit un tableau des transformations; 
// elle applique à chaque element simple nTransf nombre de tranformations,
// elle applique à chaque element simple liste de transformation qui est generée par une fonction initElemTransf
    int nCases = canvas->nColonnes*canvas->nLigne;
    float caseWidth = canvas->width/canvas->nColonnes;
    float caseHeight = canvas->height/canvas->nLigne;
    float rectlength = canvas->co.tabObj[0].tabPoints[1].x - canvas->co.tabObj[0].tabPoints[0].x;

    elemTransf ** tab = new elemTransf*[nCases];
    elemTransf * ptr;
    for(int i=0; i<nCases; i++){ // pour chaque case du tableau
        tab[i] = new elemTransf[canvas->co.n];
        
        for(int j=0; j<canvas->co.n; j++){ // pour chaque simpleObject j de composedObject co
            elemTransf * head = new elemTransf;
            ptr = head;

            for(int l=0; l<nTransf; l++){ // pour chaque transformations d'un objet simple
                initElemTransf(ptr, caseWidth, caseHeight, i, canvas->nColonnes, canvas->nColonnes, rectlength, tabColors, nColors);
                // on applique une liste des transformations generée par initElemTransf
                ptr->next = new elemTransf;
                ptr = ptr->next;
            }
            ptr->next = nullptr;
            tab[i][j] = *head;
        }
    }
    //delete ptr;
    return tab;
}

void initElemTransf_Vera_1a(elemTransf * elem, float caseWidth, float caseHeight, int numeroCase, int nColonnes, int nLignes, float rectLength, string * tabColors, int nColors){
  elem->nTransf = 3; // on initialise elemTransf elem avec une transformation numero 3 - rotation
    
  double tabAng[4] {45*M_PI/180, 90*M_PI/180, -45*M_PI/180, 0}; // tableau des angles de rotations possibles (45°, 90°, -45°, 0°)
  elem->ang = tabAng[rand()%4]; // on initialise elemTransf elem avec un angle 
  elem->xCentreRot = (numeroCase%nColonnes)*caseWidth+(caseWidth/2);
  elem->yCentreRot = (numeroCase%nLignes)*caseHeight+(caseHeight/2);
}

void initElemTransf_rand(elemTransf * elem, float caseWidth, float caseHeight, int numeroCase, int nColonnes, int nLignes, float rectLength, string * tabColors, int nColors){
  elem->nTransf = rand()%5; // on choisit aleatoirement l'une des transformations
  //elem->nTransf = 2;

  switch(elem->nTransf){
    case 0:{
      elem->x = int(caseWidth/4);
      elem->y = int(caseHeight/4);
    }

    case 1:{
      elem->color = tabColors[rand()%nColors];
      elem->colorBord = tabColors[rand()%nColors];
    }

    case 2:{
      elem->k = (rand()%100)/10.0;
      //cout << elem->k << endl;
    }

    case 3:{
      double tabAng[4] {45*M_PI/180, 90*M_PI/180, -45*M_PI/180, 0}; // tableau des angles de rotations possibles (45°, 90°, -45°, 0°)
      elem->ang = tabAng[rand()%4]; // on initialise elemTransf elem avec un angle 
      elem->xCentreRot = (numeroCase%nColonnes)*caseWidth+(caseWidth/2);
      elem->yCentreRot = (numeroCase%nLignes)*caseHeight+(caseHeight/2);
    }

    case 4:{
      elem->k = (rand()%100)/100;
    }

    default:
      break;
  }
}

void initElemTransf_Vera_1b(elemTransf * elem, float caseWidth, float caseHeight, int numeroCase, int nColonnes, int nLignes, float rectLength, string * tabColors, int nColors){
  elem->nTransf = 1; // on initialise elemTransf elem avec une transformation numero 1 - recolorage
  elem->color = tabColors[rand()%nColors];
  elem->colorBord = tabColors[rand()%nColors];
}