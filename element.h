#pragma once
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "grille.h"
#include "affichage.h"

using namespace std;

class Element {
private:
public:
    Element(); 
    ~Element() = default;
    virtual int getId() const = 0;
    
    // "a"
    void afficherInfo();
    
    // "o1" et "o2"
    void afficherIndex(Grille& grille);
    void afficherTexture(Grille& grille);

    // "f", "d" et "s"
    void deplacerPoint(int id, int nouvelleX, int nouvelleY);
    void supprimerPoint(int id);

    // Méthodes pour tracer l'orthèse ("c1" et "c2")
    void tracerLigne(Grille& grille, int x0, int y0, int x1, int y1);
    void traceDistanceMinimale();
    void traceOrdreId();
};