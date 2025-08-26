#ifndef CANVAS_HPP
#define CANVAS_HPP
#include "object.hpp"

struct Canvas {
  float width, height;
  composedObject co;
  int nLigne, nColonnes;
  elemTransf ** tabTransfGrille;
};

void init_canvas(Canvas* canvas, float w, float h, composedObject co, int nLigne, int nColonnes);

elemTransf ** init_tabTransfGrille(int nTransf, void initElemTransf(elemTransf*,float, float, int, int, int, float, string*, int),Canvas* canvas,  string * tabColors, int nColors) ;
void initElemTransf_Vera_1a(elemTransf * elem, float caseWidth, float caseHeight, int numeroCase, int nColonnes, int nLignes, float rectLength,  string * tabColors, int nColors); 
void initElemTransf_rand(elemTransf * elem, float caseWidth, float caseHeight, int numeroCase, int nColonnes, int nLignes, float rectLength, string * tabColors, int nColors);
void initElemTransf_Vera_1b(elemTransf * elem, float caseWidth, float caseHeight, int numeroCase, int nColonnes, int nLignes, float rectLength, string * tabColors, int nColors);
#endif