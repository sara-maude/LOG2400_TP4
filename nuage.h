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
#include "grille.h"
class Grille;
class Point;

using namespace std;

class Nuage: public Element {
private:
    // vector de shared ptr point
    vector<shared_ptr<Point>> points;
    Grille& grille;
    // int indexTexture = 0;
    // vector<char> texturesNuages = {'o', '#', '$'};

public:
    Nuage(vector<shared_ptr<Point>>& points, Grille& grille) : points(points), grille(grille) {}; 
    ~Nuage() = default;
    int getId() const override { return -1; }
    
    // "a"
    void afficherInfo() const override;
    
    // "o1" et "o2"
    void afficher() const override;

    // "f", "d" et "s"
    void deplacerPoint(int id, int nouvelleX, int nouvelleY) override;
    // Supprime un point du nuage. Retourne true si un point a été supprimé.
    bool supprimerPoint(int id);

    // Méthodes pour tracer l'orthèse ("c1" et "c2")
    void afficherLigne() override;
    // Accès aux points contenus (pour réindexation depuis Orthese)
    std::vector<std::shared_ptr<Point>>& getPoints() { return points; }
};