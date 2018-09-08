#include "Node.h"

Node::Node(const Location &loc, int g, int f) {
    rPos = loc.row;
    cPos = loc.col;
    GValue = g;
    FValue = f;
}

Location Node::getLocation() const {
    return Location(rPos, cPos);
}

int Node::getFValue() const {
    return FValue;
}

int Node::getGValue() const {
    return GValue;
}

void Node::calculateGValue(const int &i) {
    GValue += 10;
}

void Node::calculateFValue(const Location &locDest) {
    FValue = GValue + getHValue(locDest) * 10;
}

const int& Node::getHValue(const Location &locDest) {
    static int cd, rd, d;
    rd = locDest.row - rPos;
    cd = locDest.col - cPos;
    d = abs(rd) + abs(cd);
}