#pragma once
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <memory>
// #include "element.h"
#include "affichage.h"

using namespace std;

class DecorateurTexture {
public:
    virtual char getTexture() const = 0;
    virtual ~DecorateurTexture() = default;
};

class TextureO : public DecorateurTexture {
public:
    char getTexture() const override { return 'o'; }
};

class TextureHash : public DecorateurTexture {
public:
    char getTexture() const override { return '#'; }
};

class TextureDollar : public DecorateurTexture {
public:
    char getTexture() const override { return '$'; }
};

class Point {
private:
    int x, y;
    int id;
    vector<shared_ptr<DecorateurTexture>> textures;
public:
    Point(int x, int y, int id) : x(x), y(y), id(id) {}; 
    Point(const Point& other) = default;
    ~Point() = default;
    
    int getId() const { return id; }
    int getX() const { return x; }
    int getY() const { return y; }
    void setId(int nouvelId) { id = nouvelId; }

    vector<char> getTexture() const;
    void ajouterTexture(shared_ptr<DecorateurTexture> decor);
    void retirerTexture(shared_ptr<DecorateurTexture> decor);
    
    // "a"
    void afficherInfo() const;

    // "f", "d" et "s"
    void deplacerPoint(int id, int nouvelleX, int nouvelleY);
};