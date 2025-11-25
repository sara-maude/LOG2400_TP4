#pragma once
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "orthese.h"
#include "point.h"
#include "element.h"
#include "affichage.h"

using namespace std;

class Nuage: public Element, public Orthese {
private:
    vector<Point>& points;
    int indexTexture = 0;
    vector<char> texturesNuages = {'o', '#', '$'};
    Grille& grille;

public:
    Nuage(vector<Point>& points); 
    ~Nuage() = default;
    int getId() const override { return -1; }
    
    // "a"
    void afficherInfo();
    
    // "o1" et "o2"
    void afficherIndex(Grille& grille);
    void afficherTexture(Grille& grille);

    // "f", "d" et "s"
    void fusionnerPoints(vector<Point>& points);
    void deplacerPoint(int id, int nouvelleX, int nouvelleY);
    void supprimerPoint(int id);

    // Méthodes pour tracer l'orthèse ("c1" et "c2")
    void tracerLigne(Grille& grille, int x0, int y0, int x1, int y1);
    void traceDistanceMinimale();
    void traceOrdreId();
};