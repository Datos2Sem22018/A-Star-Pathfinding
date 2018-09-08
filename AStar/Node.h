#ifndef ASTAR_NODE_H
#define ASTAR_NODE_H
#include "Location.h"
#include <cstdlib>

const int iDim = 8;
const int jDim = 6;
const int nDir = 4;
const int iDir[nDir] = {1, 0, -1, 0};
const int jDir[nDir] = {0, 1, 0, -1};

class Node {
private:
    int rPos;
    int cPos;
    int GValue;
    int FValue;
public:
    int next;
    Node (const Location &loc, int g, int f);
    Location getLocation() const ;
    int getGValue() const ;
    int getFValue() const;
    void calculateFValue(const Location &locDest);
    void calculateGValue(const int &i);
    const int &getHValue(const Location &locDest);
    friend bool operator<(const Node & a, const Node & b) { return a.getFValue() > b.getFValue(); }
};
#endif //ASTAR_NODE_H
