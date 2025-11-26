#pragma once
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "affichage.h"
#include "point.h"

using namespace std;

class Grille {
public:
    const int largeur = 30;
    const int hauteur = 20;
    vector<vector<char>> grille;
    vector<Point>& points;
    char texture = '.';


    Grille(vector<Point>& points);
    ~Grille() = default;
    void imprimerTraceOrdreId();
    void tracerLigne(vector<vector<char>>& grille, int x0, int y0, int x1, int y1);
    void afficherGrille() const;
    void afficherIndex();
    void viderGrille();
    void afficherTexture();
    void changerTexture(char nouvelleTexture) {
        texture = nouvelleTexture;
    }
    void imprimerTraceDistanceMinimale();
};