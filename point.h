#pragma once
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <memory>
#include "element.h"

using namespace std;

class Point: public Element {
private:
    int x, y;

public:
    Point(int x, int y, int id) : x(x), y(y), Element(id) {}; 
    Point(const Point& other) = default;
    virtual ~Point() = default;
    virtual int getX() const { return x; }
    virtual int getY() const { return y; }

    virtual string getTexture() const;
    
    // "a"
    virtual void afficherInfo() const override;

    // "f", "d" et "s"
    virtual void deplacerPoint(int id, int nouvelleX, int nouvelleY);
};