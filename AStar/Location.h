#ifndef ASTAR_LOCATION_H
#define ASTAR_LOCATION_H

struct Location {
    int row, col;
    Location();
    Location(int r, int c);
    Location getLocation(int r, int c);
};

#endif //ASTAR_LOCATION_H
