#include "file.hpp"

using namespace std;

void canvas_to_file(string fileName, int width, int height, Point pCentre, float r, string couleurCirc, string bordureCirc, int nmbr, Point* tabPoints, string couleurPol, string bordurePol){
    ofstream HTMLfile(fileName);
    HTMLfile << "<!DOCTYPE html><html><body><svg width=\"" + to_string(width) + "\" height=\"" + to_string(height) + "\">";
    HTMLfile << canvas_to_svg(pCentre, r, couleurCirc, bordureCirc, nmbr, tabPoints, couleurPol, bordurePol);
    HTMLfile <<  "</svg></body></html>";
}

void canvas_exemple_to_file(int width, int height, string fileName, int numEx,  Point pCentre, float r, string couleurCirc, string bordureCirc, int nmbr, Point* tabPoints, string couleurPol, string bordurePol){
    switch (numEx) {
    case 1:
        exemple1_to_svg(fileName, width, height,r, couleurCirc, bordureCirc, nmbr, tabPoints, couleurPol, bordurePol);
        break;
    case 2: 
        exemple2_to_svg(fileName, width, height, pCentre, r, couleurCirc, bordureCirc, nmbr, tabPoints, couleurPol, bordurePol);
        break;
    case 3:
        exemple3_to_svg(fileName, width, height, pCentre, r, couleurCirc, bordureCirc, nmbr, tabPoints, couleurPol, bordurePol);
        break;
    }
}

void readFileTxt(Figure *type, string fileName, Point *pCentre, Point **TabPoints, int *nmbrSommets, float *radius, string *color, string *colorBordure ){
    ifstream file(fileName);

    if (file.is_open()) {
        string s;
        file >> s;
        if (s == "Circle") {
            *type = Circle;
            *nmbrSommets = 1;
            *TabPoints = new Point;
            file >> (*TabPoints)->x;
            file >> (*TabPoints)->y;
            file >> *radius;
        }
        else if (s == "Polygon") {
            *type = Polygon;
            file >> *nmbrSommets;
            *TabPoints = new Point[*nmbrSommets];
            int i=0;
            while (!file.eof() && i < *nmbrSommets) {
                file >> (*TabPoints+i)->x; 
                file >> (*TabPoints)[i].y;
                i++;
            }
            *radius = 0;
        }
        file.close();
    } else {
        cout << "Error!!! Unable to open file " << fileName << endl;
    }
}


void object_to_file(simpleObject o, string fileName, int width, int height){
    ofstream HTMLfile(fileName);

    if (HTMLfile.is_open()) {
        HTMLfile << "<!DOCTYPE html><html><body><svg width=\"" + to_string(width) + "\" height=\"" + to_string(height) + "\">";
        HTMLfile << simpleObject_to_svg(o);
        HTMLfile <<  "</svg></body></html>";
        HTMLfile.close();
    } else {
        cout << "Error!!! Unable to open file " << fileName << endl;
    }
}

simpleObject file_to_object (Figure *type, string fileName, Point *pCentre, Point **TabPoints, int *nmbrSommets, float *radius, string *color, string *colorBordure ){
    ifstream file(fileName);
    simpleObject o;

    if (file.is_open()) {
        string s;
        file >> s;
        *type = Circle;
        *nmbrSommets = 0;
        file >> pCentre->x;
        file >> pCentre->y;
        file >> *radius;
        file >> *color;
        file >> *colorBordure;
        if (s == "Polygon") {
            *type = Polygon;
            file >> *nmbrSommets;
            *TabPoints = new Point[*nmbrSommets];
            int i=0;
            while (!file.eof() && i < *nmbrSommets) {
                file >> (*TabPoints)[i].x; 
                file >> (*TabPoints)[i].y;
                i++;
            }
        }
        file.close();

        o = init_object(*type,*pCentre, *radius, *nmbrSommets, *TabPoints, *color, *colorBordure);
    } else {
        cout << "Error!!! Unable to open file " << fileName << endl;
    }
    return o;
}

composedObject files_to_composedObject(string* tabFiles, int n){
    simpleObject * tabObj = new simpleObject[n];
    Point pCentre;
    Point* tabPoints;
    int nmbrSommets;
    float radius;
    Figure type;
    string color;
    string colorBordure;

    for(int i=0; i<n; i++)
        tabObj[i] = file_to_object(&type, tabFiles[i], &pCentre, &tabPoints, &nmbrSommets, &radius, &color, &colorBordure);
    
    composedObject co = init_composedObject(tabObj, n);
    return co;
}

composedObject file_to_composedObject(string fileName){
    ifstream file(fileName);
    composedObject co;
    

    if (file.is_open()) {
        string line, s;
        getline(file, line);
        int n = stoi(line);
        int i = 0;
        simpleObject *tabObj = new simpleObject[n];

        while (getline(file, line) && i < n) {
            istringstream iss(line);
            iss >> s;
            Figure type = Circle;
            int nmbrSommets = 0;
            float radius = 0; 
            Point pCentre;
            string color, colorBordure;
            iss >> pCentre.x;
            iss >> pCentre.y;
            iss >> radius;
            iss >> color;
            iss >> colorBordure;

            if (s == "Polygon") {
                type = Polygon;
                iss >> nmbrSommets;
                Point* tabPoints = new Point[nmbrSommets];
                for (int j = 0; j < nmbrSommets; ++j) {
                    iss >> tabPoints[j].x;
                    iss >> tabPoints[j].y;
                }
                tabObj[i] = init_object(type, pCentre, radius, nmbrSommets, tabPoints, color, colorBordure);
                tabPoints = nullptr;
            } else {
                tabObj[i] = init_object(type, pCentre, radius, nmbrSommets, nullptr, color, colorBordure);
            }
            ++i;
        }
        co = init_composedObject(tabObj, i);
        file.close();
    } else {
        cout << "Error!!! Unable to open file " << fileName << endl;
    }
    return co;
}

void composedObject_to_file (composedObject co, string fileName, int width, int height){
    ofstream HTMLfile(fileName);

    if (HTMLfile.is_open()) {
        HTMLfile << "<!DOCTYPE html><html><body><svg width=\"" + to_string(width) + "\" height=\"" + to_string(height) + "\">";
        HTMLfile << composedObject_to_svg(co);
        HTMLfile <<  "</svg></body></html>";
        HTMLfile.close();
    } else {
        cout << "Error!!! Unable to open file " << fileName << endl;
    }
}
void canvas_transform_composed_to_svg(Canvas canvas, string fileName){
    ofstream HTMLfile(fileName);
    if (HTMLfile.is_open()) {
        composedObject coCopie;
        int x = canvas.width/canvas.nColonnes;
        int y = canvas.height/canvas.nLigne;        
        HTMLfile << "<!DOCTYPE html><html><body><svg width=\"" + to_string(canvas.width) + "\" height=\"" + to_string(canvas.height) + "\">" << '\n';
        for(int j=0; j<canvas.nLigne; j++){
            for (int i=0; i<canvas.nColonnes; i++){
                copieComposedObject(&canvas.co, &coCopie);
                translate_composedObject(&coCopie, i*x, j*y);

                for(int obj=0; obj<canvas.co.n; obj++){
                    elemTransf * ptr = &(canvas.tabTransfGrille[j*canvas.nColonnes+i][obj]);
                    //cout << "k" << ptr->k << endl;
                    choose_fonc(*ptr, &coCopie.tabObj[obj]); 
                    while(ptr->next != nullptr){
                        ptr = ptr->next;
                        choose_fonc(*ptr,  &coCopie.tabObj[obj]);
                    }
                }
                HTMLfile << composedObject_to_svg(coCopie);
                HTMLfile << '\n';
            }
        }
        HTMLfile << "</svg></body></html>";
    }
    else {
        cout << "Error!!! Unable to open file " << fileName << endl;
    }
}