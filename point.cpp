#include "point.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

void Point::afficherInfo() const {
    cout << id << ":" << " (" << x << "," << y << ") textures: '" << texture << "'\n ";
}

void Point::deplacerPoint(int id, int nouvelleX, int nouvelleY) {
    x = nouvelleX;
    y = nouvelleY;
}