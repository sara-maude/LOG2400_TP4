#pragma once
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <memory>

using namespace std;

class Element {
protected:
    int id;
public:
    Element(int id): id(id) {};
    ~Element() = default;
    int getId() {
        return id;
    };
    
    void setId(int nouvelId) { 
        id = nouvelId; 
    }
    
    virtual void afficherInfo() const = 0;
};