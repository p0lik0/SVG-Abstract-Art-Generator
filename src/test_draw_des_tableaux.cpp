#include <iostream>
#include <fstream>
#include "file.hpp"
#include "getInfo.hpp"
#include "object.hpp"
#include "canvas.hpp"

using namespace std;

// Program expects at least 6 arguments: 
// ./test_fonc3 dummy file1.txt file2.txt file3.txt file4.txt file5.txt
// where file1..3 → random transformations
// file4 → special transformation Vera_1a
// file5 → special transformation Vera_1b

int main(int argc, char** argv) {
    if (argc < 7) {
        cerr << "Usage: " << argv[0] 
             << " dummy file1.txt file2.txt file3.txt file4.txt file5.txt" << endl;
        return 1;
    }

    Canvas canvas;
    string tabColors[9] {"black", "white", "blue", "green", "yellow", "orange", "pink", "purple", "red"};

    // First 3 files → apply random transformations
    for (int i = 0; i < 3; i++) {
        string filename = argv[i + 2];
        cout << "Processing (random transform): " << filename << endl;

        composedObject co = file_to_composedObject(filename);
        init_canvas(&canvas, 1000, 1000, co, 20, 20);
        canvas.tabTransfGrille = init_tabTransfGrille(3, initElemTransf_rand, &canvas, tabColors, 9);

        string outFile = "test_rand_tableau_" + to_string(i + 1) + ".html";
        canvas_transform_composed_to_svg(canvas, outFile);
        cout << "Saved: " << outFile << endl;
    }

    // Fourth file → apply Vera_1a transformation
    {
        string filename = argv[5];
        cout << "Processing (Vera_1a): " << filename << endl;

        composedObject co = file_to_composedObject(filename);
        init_canvas(&canvas, 1000, 1000, co, 20, 20);
        canvas.tabTransfGrille = init_tabTransfGrille(3, initElemTransf_Vera_1a, &canvas, tabColors, 9);

        string outFile = "test_rand_tableau_4.html";
        canvas_transform_composed_to_svg(canvas, outFile);
        cout << "Saved: " << outFile << endl;
    }

    // Fifth file → apply Vera_1b transformation
    {
        string filename = argv[6];
        cout << "Processing (Vera_1b): " << filename << endl;

        composedObject co = file_to_composedObject(filename);
        init_canvas(&canvas, 1000, 1000, co, 20, 20);
        canvas.tabTransfGrille = init_tabTransfGrille(3, initElemTransf_Vera_1b, &canvas, tabColors, 9);

        string outFile = "test_rand_tableau_5.html";
        canvas_transform_composed_to_svg(canvas, outFile);
        cout << "Saved: " << outFile << endl;
    }

    cout << "✅ All files processed successfully!" << endl;
    return 0;
}
