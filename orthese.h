#pragma once
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <memory>
#include "grille.h"
#include "point.h"
#include "nuage.h"
#include "element.h"
#include "affichage.h"
class Grille;
class Point;

using namespace std;

class Orthese: public Element {
private:
    vector<shared_ptr<Element>> elements;
    Grille grille;

public:
    Orthese(vector<Point>& points); 
    ~Orthese() = default;
    int getId() const override { return -1; }
    
    // "a"
    void afficherInfo() const override;
    
    // "o1" et "o2"
    void afficher() const override;

    // "f", "d" et "s"
    // fusionner point prend une liste de id
    void fusionnerPoints(vector<int> ids);
    void deplacerPoint(int id, int nouvelleX, int nouvelleY);
    void supprimerPoint(int id);

    // Méthodes pour tracer l'orthèse ("c1" et "c2")
    void afficherLigne() override;
};