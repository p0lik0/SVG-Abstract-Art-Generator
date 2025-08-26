#ifndef OBJECT_HPP_ //si la variable de compilation n’est pas connue (d´efinie)
#define OBJECT_HPP_ //on la d´efinit
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

struct Point{
    float x,y;
};

enum Figure {Polygon, Circle};

struct simpleObject{
    Figure figure;
    Point pCentre;
    float rayon;
    string couleur, bordureCouleur;
    int nmbrSommets;
    Point * tabPoints;
};

struct composedObject{
    int n;
    simpleObject * tabObj;
};

struct elemTransf {
    int nTransf; // numero de transformation 
    float x, y; // donnes pour translation
    string color, colorBord; // donnes pour recolorer
    float k; // donnes pour resize
    float ang, xCentreRot, yCentreRot; // donnes pour rotatipon
    elemTransf * next;
};

Point getPoint();
Point* getTabPoints(int n);

elemTransf ** init_tabTransfGrille_Vera_1a(int nCases, int nObj, float caseWidth, float caseHeight);
 // nCases = nColonnes*nLignes; nObj = nmbr des objects simple composants objet composé

simpleObject init_circle(Point pCentre, float r, string couleur, string bordure);
simpleObject init_polygon(int nmbr, Point* tabPoints, string couleur, string bordure);
simpleObject init_object(Figure f, Point pCentre, float r, int nmbr, Point* tabPoints, string couleur, string bordure);
void printObj(simpleObject o);
void copie(simpleObject* o, simpleObject *oCopie);

composedObject init_composedObject(simpleObject * tabObj, int n);
void copieComposedObject(composedObject* co, composedObject* coCopie);
void printCobj(composedObject co);


void choose_fonc(elemTransf e, simpleObject * o);

void translate_object(simpleObject* o, float x, float y);
void translate_composedObject(composedObject* co, float x, float y);

void recolorer_composedObject(composedObject* co, string color, string colorBord);

void resize_object(simpleObject* o, float k);
void resize_composedObject(composedObject* co, float k);


#endif //fin des fonctions `a compiler si la variable de compilation n’est pas d´efinie