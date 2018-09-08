#include <iostream>
#include <iomanip>
#include <ctime>
#include "Location.h"
#include "Node.h"
#include <queue>
using namespace std;
int squares[iDim][jDim];
int closedNodes[iDim][jDim];
int openNodes[iDim][jDim];
int dirMap[iDim][jDim];

string PathFinding (const Location &locStart, const Location &locEnd) {
    static priority_queue<Node> q[2];
    static int qi;
    static Node* pNode1;
    static Node* pNode2;
    static int i, j, row, col, iNext, jNext;
    static char c;
    qi = 0;
    for (int j = 0; j < jDim; ++j) {
        for (int i = 0; i < iDim; ++i) {
            closedNodes[i][j] = 0;
            openNodes[i][j] = 0;
        }
    }
    pNode1 = new Node(locStart, 0, 0);
    pNode1->calculateFValue(locEnd);
    q[qi].push(*pNode1);
    while (!q[qi].empty()) {
        pNode1 = new Node(q[qi].top().getLocation(), q[qi].top().getGValue(), q[qi].top().getFValue());
        row = pNode1->getLocation().row;
        col = pNode1->getLocation().col;
        cout << "row, col=" << row << "," << col << endl;
        q[qi].pop();
        openNodes[row][col] = 0;
        closedNodes[row][col] = 1;
        if (row == locEnd.row && col == locEnd.col) {
            cout << endl;
            for(j = jDim - 1; j >= 0; j--) {
                for(i = 0; i < iDim; i++) {
                    cout << dirMap[i][j];
                }
                cout << endl;
            }
            cout << endl;
            string path = "";
            while(!(row == locStart.row && col == locStart.col)) {
                j = dirMap[row][col];
                c = '0' + (j + nDir/2) % nDir;
                path = c + path;
                row += iDir[j];
                col += jDir[j];
            }
            delete pNode1;
            while (!q[qi].empty()) {
                q[qi].pop();
                return path;
            }
        }
        for (int i = 0; i < nDir; ++i) {
            iNext = row + iDir[i];
            jNext = col + jDir[j];
            if(!(iNext < 0 || iNext > iDim - 1 || jNext < 0 || jNext > jDim - 1 || squares[iNext][jNext] == 1 || closedNodes[iNext][jNext] == 1)) {
                pNode2 = new Node(Location(iNext, jNext), pNode1->getGValue(), pNode1->getFValue());
                pNode2->calculateGValue(i);
                pNode2->calculateFValue(locEnd);
                if(openNodes[iNext][jNext] == 0) {
                    openNodes[iNext][jNext] = pNode2->getFValue();
                    q[qi].push(*pNode2);
                    dirMap[iNext][jNext] = (i + nDir/2) % nDir;
                }
                else if (openNodes[iNext][jNext] > pNode2->getFValue()) {
                    openNodes[iNext][jNext] = pNode2->getFValue();
                    dirMap[iNext][jNext] = (i + nDir/2) % nDir;
                    while(!(q[qi].top().getLocation().row == iNext && q[qi].top().getLocation().col == jNext)) {
                        q[1 - qi].push(q[qi].top());
                        q[qi].pop();
                    }
                    q[qi].pop();
                    q[qi].push(*pNode2);
                } else {
                    delete pNode2;
                }
            }
        }
        delete pNode1;
    }
    return "";
}

int main() {
    for(int j = 0; j < jDim; j++) {
        for(int i = 0; i < iDim; i++) {
            squares[i][j] = 0;
        }
    }
    int iStart = 2, jStart = 3, iEnd = 6,jEnd = 3;
    cout << "Grid Size (iDim,jDim): "<< iDim << "," << jDim << endl;
    cout << "Start: " << iStart<<","<< jStart << endl;
    cout << "Finish: " << iEnd<<","<< jEnd << endl;
    clock_t start = clock();
    string path = PathFinding(Location(iStart, jStart), Location(iEnd, jEnd));
    clock_t end = clock();
    int time = int(end - start);
    cout << "Time (ms): "<< time << endl;
    cout << "path: " << path << endl;
    if(path.length() > 0) {
        char c;
        int m, n;
        int i = iStart;
        int j = jStart;
        squares[i][j] = 2;
        for(m = 0; m < path.length(); m++) {
            c = path.at(m);
            n = atoi(&c);
            i = i + iDir[n];
            j = j + jDir[n];
            squares[i][j] = 3;
        }
        squares[i][j] = 4;
        for(j = jDim - 1; j >= 0; j--) {
            for(i = 0; i < iDim; i++) {
                if(squares[i][j] == 0)
                    cout << ".";
                else if(squares[i][j] == 1)
                    cout << "O";
                else if(squares[i][j] == 2)
                    cout << "I";
                else if(squares[i][j] == 3)
                    cout << "P";
                else if(squares[i][j] == 4)
                    cout << "F";
            }
            cout << endl;
        }
    }
    return 0;
}