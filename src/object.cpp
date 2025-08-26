#include "object.hpp"

//une fonction pour saisir les coordonnées d'un point
Point getPoint(){
    Point p;
    cout << "Coords de x : ";
    cin >> p.x;
    cout << "Coords de y : ";
    cin >> p.y;
    return p;
}

//une fonction pour remplir un tableau avec les coordeonnées des points
Point* getTabPoints(int n){
    Point* tabP = new Point[n];
    for(int i=0; i<n; i++)
        tabP[i] = getPoint();
    return tabP;
}

//une fonction qui crée et initialise un objet simple représentant un cercle
simpleObject init_circle(Point pCentre, float r, string couleur, string bordure){
    simpleObject c;
    c.bordureCouleur = bordure;
    c.couleur = couleur;
    c.figure = Circle;
    c.nmbrSommets = 0;
    c.pCentre = pCentre;
    c.rayon = r;
    return c;
}

//une fonction qui crée et initialise un objet simple représentant un polygon
simpleObject init_polygon(int nmbr, Point* tabPoints, string couleur, string bordure){
    simpleObject p;
    p.bordureCouleur = bordure;
    p.couleur = couleur;
    p.figure = Polygon;
    p.nmbrSommets = nmbr;
    p.tabPoints = tabPoints;
    return p;
}

//une fonction qui crée et initialise un objet simple, soit un cercle soit un polygone, en fonction de `f`.
simpleObject init_object(Figure f, Point pCentre, float r, int nmbr, Point* tabPoints, string couleur, string bordure){
    simpleObject o;
    if(f == Circle){
        o.bordureCouleur = bordure;
        o.couleur = couleur;
        o.figure = Circle;
        o.nmbrSommets = 0;
        o.pCentre = pCentre;
        o.rayon = r;
    }
    else if (f == Polygon){
        o.bordureCouleur = bordure;
        o.couleur = couleur;
        o.figure = Polygon;
        o.nmbrSommets = nmbr;
        o.tabPoints = tabPoints;
    }
    return o;
}
//une fonction qui affiche les détails d'un objet simple
void printObj(simpleObject o){
    cout << "Figure : " << o.figure << endl;
    if(o.figure == Circle){
        cout << "Point de centre : " << o.pCentre.x << " " << o.pCentre.y << endl;
        cout << "Rayon : " << o.rayon << endl;
        cout << "Couleur : " << o.couleur << endl;
        cout << "Couleur de bordure: " << o.bordureCouleur << endl;
    }
    else if (o.figure == Polygon){
        cout << "Nmbr de sommets : " << o.nmbrSommets << endl;
        cout << "TabPoints : " << endl;
        for (int i=0; i<o.nmbrSommets; i++){
            cout << o.tabPoints[i].x << " " << o.tabPoints[i].y << "; " << endl;
        }
        cout << "Couleur : " << o.couleur << endl;
        cout << "Couleur de bordure: " << o.bordureCouleur << endl;
    }
}

//une fonction qui copie un objet simple
void copie(simpleObject* o, simpleObject* oCopie){
    *oCopie = {o->figure, o->pCentre, o->rayon, o->couleur, o->bordureCouleur, o->nmbrSommets};
    Point * tabPointsCopie = new Point[o->nmbrSommets];
    for(int i=0; i<o->nmbrSommets; i++){
        tabPointsCopie[i] = (o->tabPoints)[i];
    }
    oCopie->tabPoints = tabPointsCopie;
}

//une fonction qui initialise un objet composé avec un tableau d'objets simples et le nombre d'objets dans le tableau.
composedObject init_composedObject(simpleObject * tabObj, int n){
    composedObject co;
    co.n = n;
    co.tabObj = tabObj;
    return co;
}

//une fonction qui copie un objet composé.
void copieComposedObject(composedObject* co, composedObject* coCopie){
// co - source, coCopie - destination
    simpleObject * tabObj = new  simpleObject[co->n];
    for(int i=0; i<co->n; i++){
        copie(&(co->tabObj[i]), &(tabObj[i]));
    }
    *coCopie = init_composedObject(tabObj, co->n);
}

//une fonction qui affiche les détails de tous les objets simples contenus dans un objet composé
void printCobj(composedObject co){
    for(int i = 0; i<co.n; i++){
        printObj(co.tabObj[i]);
        cout << endl;
    }
}

void translate_object(simpleObject* o, float x, float y){
    if (o->figure == Circle){
        o->pCentre.x += x;
        o->pCentre.y += y;
    }
    else if (o->figure == Polygon){
        for (int i=0; i<o->nmbrSommets; i++){
            o->tabPoints[i].x += x;
            o->tabPoints[i].y += y;
        }
    }
}

void translate_composedObject(composedObject* co, float x, float y){
    for(int i=0; i<co->n; i++){
        translate_object(&(co->tabObj[i]), x, y);
    }
}

void recolorer_object(simpleObject* o, string color, string colorBord){
    o->couleur = color;
    o->bordureCouleur = colorBord;
}


void recolorer_composedObject(composedObject* co, string color, string colorBord){
    for(int i=0; i<co->n; i++){
        recolorer_object(&(co->tabObj[i]), color, colorBord);
    }
}

void resize_object(simpleObject* o, float k){
    if (o->figure == Circle){
        o->rayon *= k;
    }
    else if (o->figure == Polygon){
        float xG=0, yG=0;
        for (int i=0; i<o->nmbrSommets; i++){
            xG += o->tabPoints[i].x;
            yG += o->tabPoints[i].y;
        }
        xG /= o->nmbrSommets; 
        yG /= o->nmbrSommets;
        for (int i=0; i<o->nmbrSommets; i++){
            o->tabPoints[i].x = xG + k*(o->tabPoints[i].x - xG);

            o->tabPoints[i].y = yG + k*(o->tabPoints[i].y - yG);
        }
    }
}

void resize_composedObject(composedObject* co, float k){
    for(int i=0; i<co->n; i++){
        resize_object(&(co->tabObj[i]), k);
    }
}

void rotate_object(simpleObject * o, float ang, float xCentreRot, float yCentreRot){
    // ang *= M_PI / 180;
    if (o->figure == Circle){
        o->pCentre.x = xCentreRot + cos(ang)*(o->pCentre.x - xCentreRot) + sin(ang)*(o->pCentre.y - yCentreRot);
        o->pCentre.y = yCentreRot - sin(ang)*(o->pCentre.x - xCentreRot) + cos(ang)*(o->pCentre.y - yCentreRot);
    }
    else if (o->figure == Polygon){
        for (int i=0; i<o->nmbrSommets; i++){
            float x = xCentreRot + cos(ang)*(o->tabPoints[i].x - xCentreRot) + sin(ang)*(o->tabPoints[i].y - yCentreRot);
            o->tabPoints[i].y = yCentreRot - sin(ang)*(o->tabPoints[i].x - xCentreRot) + cos(ang)*(o->tabPoints[i].y - yCentreRot);
            o->tabPoints[i].x = x;
        }
    }
}

void rotate_composedObject(composedObject * co, float ang, float xCentreRot, float yCentreRot){
    for(int i=0; i<co->n; i++){
        rotate_object(&(co->tabObj[i]), ang, xCentreRot, yCentreRot);
    }
}

void resize_longeur_rectangle_object(simpleObject * o, int k){
    o->tabPoints[1].x *= k;
    o->tabPoints[2].x *= k;
}

void choose_fonc(elemTransf e, simpleObject * o){
    switch (e.nTransf){

        case 0:{
            translate_object(o, e.x, e.y);
            break;
        }
        case 1:{
            recolorer_object(o, e.color, e.colorBord);
            break;
        }
        case 2:{
            resize_object(o, e.k);
            break;
        }
        case 3:{
            rotate_object(o, e.ang, e.xCentreRot, e.yCentreRot);
            break;
        }

        default:
            break;
    }
}