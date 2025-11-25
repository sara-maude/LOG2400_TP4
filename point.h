// #pragma once
// #include <string>
// #include <vector>
// #include <cmath>
// #include <iostream>
// #include <sstream>
// #include <algorithm>
// #include "element.h"
// #include "affichage.h"

// using namespace std;

// class Point: public Element {
// private:
//     int x, y;
//     int id;
//     char texture;
// public:
//     Point(int x, int y) : x(x), y(y) {}; 
//     ~Point() = default;
//     int getId() const override { return id; }
    
//     // "a"
//     void afficherInfo();

//     // "f", "d" et "s"
//     void deplacerPoint(int id, int nouvelleX, int nouvelleY);
//     void supprimerPoint(int id);
// };