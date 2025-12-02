#pragma once
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "point.h"

using namespace std;

class Grille {
public:
    const int largeur = 30;
    const int hauteur = 20;
    vector<vector<char>> grille;


    Grille();
    ~Grille() = default;

    void tracerLigne(int x0, int y0, int x1, int y1);
    void imprimerGrille() const;
    void viderGrille();
};