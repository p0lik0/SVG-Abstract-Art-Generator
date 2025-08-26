#include "draw_svg.hpp"

//une fonction qui retourne une chaîne de caractères représentant un cercle en SVG avec les attributs correspondants.
string circle_to_svg(Point pCentre, float r, string couleur, string bordure){
    return "<circle cx=\"" + to_string(pCentre.x) + "\" cy=\"" + to_string(pCentre.y) + "\" r=\"" + to_string(r) + "\" fill=\"" + couleur + "\" stroke=\"" + bordure + "\"/>";
}

//une fonction qui retourne une chaîne de caractères représentant un polygon en SVG avec les attributs correspondants.
string polygon_to_svg(int nmbr, Point* tabPoints, string couleur, string bordure){
    string s = "<polygon points=\"";
    for (int i=0; i<nmbr; i++)
        s += to_string(tabPoints[i].x) + "," + to_string(tabPoints[i].y) + " ";
    s += "\" fill=\"" + couleur + "\" stroke=\"" + bordure + "\"/>";
    return s;
}


//une fonction qui prend la largeur et la hauteur du canvas, les informations pour dessiner un cercle et un polygon
string canvas_to_svg(Point pCentre, float r, string couleurCirc, string bordureCirc, int nmbr, Point* tabPoints, string couleurPol, string bordurePol){
    string s ;
    s += circle_to_svg(pCentre, r, couleurCirc, bordureCirc);
    s += polygon_to_svg(nmbr, tabPoints, couleurPol, bordurePol);
    return s;
}

//une fonction qui retourne la chaîne de caractères représentant l'objet SVG (circle ou polygon)
string simpleObject_to_svg(simpleObject o){
    string s;
    if (o.figure == Circle){
        s += circle_to_svg(o.pCentre, o.rayon, o.couleur, o.bordureCouleur);
    }
    else if (o.figure == Polygon){
        s += polygon_to_svg(o.nmbrSommets, o.tabPoints, o.couleur, o.bordureCouleur);
    }
    return s;
}

//une fonction qui retourne une chaîne de caractères représentant l'objet composé en SVG (circle ou polygon)
string composedObject_to_svg(composedObject co){
    string s = "";
    for(int i=0; i<co.n; i++){
        s += simpleObject_to_svg(co.tabObj[i]);
    }
    return s;
}

//une fonction qui crée un fichier HTML avec un canvas SVG contenant le cercle et le polygone
void exemple1_to_svg(string fileName, int width, int height, float r, string couleurCirc, string bordureCirc, int nmbr, Point* tabPoints, string couleurPol, string bordurePol){
    ofstream HTMLfile(fileName);
    string s = "<!DOCTYPE html><html><body><svg width=\"" + to_string(width) + "\" height=\"" + to_string(height) + "\">";

    Point pCentre;
    pCentre.x = 100;
    pCentre.y = 100;

    s += circle_to_svg(pCentre, r, couleurCirc, bordureCirc);
    s += polygon_to_svg(nmbr, tabPoints, couleurPol, bordurePol);
    s += "</svg></body></html>";
    HTMLfile << s;
}

//une fonction qui crée un fichier HTML avec un canvas SVG contenant le cercle et le polygone
void exemple3_to_svg(string fileName, int width, int height, Point pCentre, float r, string couleurCirc, string bordureCirc, int nmbr, Point* tabPoints, string couleurPol, string bordurePol){
    ofstream HTMLfile(fileName);
    string s = "<!DOCTYPE html><html><body><svg width=\"" + to_string(width) + "\" height=\"" + to_string(height) + "\">";

    s += polygon_to_svg(nmbr, tabPoints, couleurPol, bordurePol);
    s += circle_to_svg(pCentre, r, couleurCirc, bordureCirc);
    s += "</svg></body></html>";
    HTMLfile << s;
}

//une fonction qui crée un fichier HTML avec un canvas SVG contenant le cercle et le polygone
void exemple2_to_svg(string fileName, int width, int height, Point pCentre, float r, string couleurCirc, string bordureCirc, int nmbr, Point* tabPoints, string couleurPol, string bordurePol){
    ofstream HTMLfile(fileName);
    string s = "<!DOCTYPE html><html><body><svg width=\"" + to_string(width) + "\" height=\"" + to_string(height) + "\">";

    s += circle_to_svg(pCentre, r, couleurCirc, bordureCirc);
    s += polygon_to_svg(nmbr, tabPoints, couleurPol, bordurePol);
    s += "</svg></body></html>";
    HTMLfile << s;
}

string canvas_composed_to_svg(Canvas canvas){
    string s;
    s += "<!DOCTYPE html><html><body><svg width=\"" + to_string(canvas.width) + "\" height=\"" + to_string(canvas.height) + "\">";
    s += composedObject_to_svg(canvas.co);
    s += "</svg></body></html>";
    return s;
}