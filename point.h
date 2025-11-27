#pragma once
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <memory>
#include "element.h"
// #include "affichage.h"

using namespace std;

class Point: public Element {
private:
    int x, y;
    vector<shared_ptr<DecorateurTexture>> textures;

public:
    Point(int x, int y) : x(x), y(y) {}; 
    Point(const Point& other) = default;
    ~Point() = default;
    int getX() const { return x; }
    int getY() const { return y; }

    vector<char> getTexture() const;
    void ajouterTexture(shared_ptr<DecorateurTexture> decor) override;
    void retirerTexture(shared_ptr<DecorateurTexture> decor);
    
    // "a"
    void afficherInfo() const override;

    // "f", "d" et "s"
    void deplacerPoint(int id, int nouvelleX, int nouvelleY);
};