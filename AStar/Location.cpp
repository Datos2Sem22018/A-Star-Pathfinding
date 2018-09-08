#include "Location.h"

Location::Location() {
    row = col = 0;
}

Location::Location(int r, int c) {
    r = row;
    c = col;
}

Location Location::getLocation(int r, int c) {
    return Location(r, c);
}