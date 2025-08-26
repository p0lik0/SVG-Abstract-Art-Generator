#ifndef DRAW_SVG_HPP_ //si la variable de compilation n’est pas connue (d´efinie)
#define DRAW_SVG_HPP_ //on la d´efinit
#include <iostream>
#include <fstream>
#include "object.hpp"
#include "canvas.hpp"

using namespace std;

string circle_to_svg(Point pCentre, float r, string couleur, string bordure);

string polygon_to_svg(int nmbr, Point* tabPoints, string couleur, string bordure);

string aLaVerlanMolnar(int n, int decalage, int width, int height, Point pCentre, float r, string couleurCirc, string bordureCirc, int nmbr, Point* tabPoints, string couleurPol, string bordurePol);

string canvas_to_svg(Point pCentre, float r, string couleurCirc, string bordureCirc, int nmbr, Point* tabPoints, string couleurPol, string bordurePol);

void exemple1_to_svg(string fileName, int width, int height, float r, string couleurCirc, string bordureCirc, int nmbr, Point* tabPoints, string couleurPol, string bordurePol);

void exemple3_to_svg(string fileName, int width, int height, Point pCentre, float r, string couleurCirc, string bordureCirc, int nmbr, Point* tabPoints, string couleurPol, string bordurePol);

void exemple2_to_svg(string fileName, int width, int height, Point pCentre, float r, string couleurCirc, string bordureCirc, int nmbr, Point* tabPoints, string couleurPol, string bordurePol);

string simpleObject_to_svg(simpleObject o);

string composedObject_to_svg(composedObject co);

string canvas_composed_to_svg(Canvas canvas);

#endif //fin des fonctions `a compiler si la variable de compilation n’est pas d´efinie