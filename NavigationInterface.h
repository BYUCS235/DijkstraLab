#ifndef NAVIGATIONINTERFACE_H
#define NAVIGATIONINTERFACE_H

#include <iostream>
#include <string>
#include <queue>

using namespace std;

class NavigationInterface {
public:
    NavigationInterface() {}
    virtual ~NavigationInterface() {}

    // This function reads in the contents of the file _mapName.
    // If a file of this name does not exist or the file format is incorrect your function should read false (true otherwise)
    virtual bool readNetwork(string _mapName) = 0;

    // This function computes and returns the least-cost path from node indexed _startInd to node indexed as _endInd
    // for the map that was last read (in the readMap function).  The resulting path must be stored in an integer queue
    // with each entry in the queue denoting the next node in the path.  First front of the queue should be _startInd
    // and the back of the queue should be _endInd.
    // For example, in map1.txt, solveMap(13, 1) should return the shortest path from node 13 to node 1, which is:
    //      13, 9, 10, 7, 3, 2, 1
    // If no road netowork has been read in or getting from node _startInd to _endInd is not possible, then this function should return
    // an empty queue
    virtual queue<int> computeShortestPath(int _startInd, int _endInd) = 0;

    // prints out to the console the path stored in _path
    virtual void printPath(queue<int> _path) = 0;
};

#endif
