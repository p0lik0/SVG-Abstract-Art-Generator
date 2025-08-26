#ifndef FILE_HPP_ //si la variable de compilation n’est pas connue (d´efinie)
#define FILE_HPP_ //on la d´efinit
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "object.hpp"
#include "draw_svg.hpp"

using namespace std;

void canvas_to_file(string fileName, int width, int height, Point pCentre, float r, string couleurCirc, string bordureCirc, int nmbr, Point* tabPoints, string couleurPol, string bordurePol);

void canvas_exemple_to_file(int width, int height, string fileName, int numEx,  Point pCentre, float r, string couleurCirc, string bordureCirc, int nmbr, Point* tabPoints, string couleurPol, string bordurePol);

void object_to_file(simpleObject o, string fileName, int width, int height);

void readFileTxt(Figure *type, string fileName, Point *pCentre, Point **TabPoints, int *nmbrSommets, float *radius, string *color, string *colorBordure );

simpleObject file_to_object
(Figure *type, string fileName, Point *pCentre, Point **TabPoints, int *nmbrSommets, float *radius, string *color, string *colorBordure );

composedObject files_to_composedObject(string* tabFiles, int n);

composedObject file_to_composedObject(string fileName);

void composedObject_to_file (composedObject co, string fileName, int width, int height);

void canvas_transform_composed_to_svg(Canvas canvas, string fileName);

#endif //fin des fonctions `a compiler si la variable de compilation n’est pas d´efinie