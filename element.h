#pragma once
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <memory>
#include "texture.h"

using namespace std;

class Element {
private:
    static int compteur;
protected:
    int id;
public:
    Element(): id(compteur++) {};
    ~Element() = default;
    int getId() {
        return id;
    };
    
    void setId(int nouvelId) { 
        id = nouvelId; 
    }
    
    // "a"
    virtual void afficherInfo() const = 0;
    virtual void ajouterTexture(shared_ptr<DecorateurTexture> decor) = 0;
};