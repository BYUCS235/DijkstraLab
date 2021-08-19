# Navigation Lab
 
## Purposes:
This lab is intended to:
(1)	Give you experience implementing queues and priorities queues in C++.  
(2)	Help you understand the usefulness of queues and priorities in computer programs (as opposed to just always using lists)
 
## Overview:
You’ve been hired as an intern for a new driverless care (start-up) company.  The company wants you to create a navigation system for their cars.  Your first step in creating this navigation system is to create a computer program that takes as input a road network and outputs the shortest (with respect to time-to-travel) path from any desired start location in the road network to any ending location in the road network.   In this lab, you will carry out that task using a simple algorithm that is most easily implemented using priority queues and queues.

To help you on this lab, the rest of the specs for this lab include three sections: (1) A section talking about the code base you will work from, (2) a section discuss the algorithm you will implement for computing the shortest path, and (3) information about implementing priority queues in C++ and other (hopefully helpful) implementation details.

## Code
To do this project, you should work from this code.  This code includes the following files:

### main.cpp:
This main.cpp file processes the inputs, instantiates a class that you will write, and calls the functions in your class.  Finally, it creates the file Map.bmp, which displays the road network and the shortest path computed by your program.  You don’t need to modify this file.   It takes as as input (from the command line) a road network, a start node in the network, and an end node in the network. Once you create a dummy class that implements NavigationInterface.h and compile the code along with main.cpp and graphicsStuff.cpp, you can run the program as follows:

./navigate [roadNetwork] [startNode] [endNode]

For example:

./navigate ../Maps/map1.txt 12 3

finds the shortest path from Node 12 to Node 3 in the road network defined in the file ../Maps/map1.txt.

### graphicsStuff.cpp:
This file creates the file Map.bmp displaying the shortest path your program computes

### NavigateInterface.cpp:
An interface file describing the abstract class that you should implement.

### Map files:
The “Maps” folder contains some sample road networks to help you start to test your program.  These map files are in the following format:

Line 1 specifies the number of nodes in the network.  For example, in map1.txt, there are 15 nodes in the network.

Lines 2 specifies the cost for getting from node 0 to all other nodes in the network.  A cost of -1 indictates that there is no direct path from node 0 to a node.  For example, in map1.txt, there is a cost of 20 to get to node 4 from node 0, but you cannot get directly to any other node from node 0.

Lines 3 through N+1 specifies the costs for getting from nodes 1 though N (where N is the number of nodes read in on Line 1) to all other nodes in the network.

Lines N+2 through 2N+1 specify the coordinates of each node in the network.  Your algorithm doesn’t actually need this information so you can ignore it.  But graphicsStuff.cpp uses the information to create a graphical representation of the road network.


## The Algorithm
To complete this lab, you need to implement the abstract class NavigateInterface.h.  To do this, you should create the files Navigate.h and Navigate.cpp.  The class you create in these files must implement three functions: readNetwork, computeShortestPath, and printPath.  Specifications for these functions are given in NavigateInterace.h.

We will use a simplified version of Dijkstra’s algorithm to find the shortest path from startNode to endNode.  This algorithm uses a priority queue in which we store custom objects into the priority queue.  Each object has two fields: a cost field and a path field.  Let object.cost be the cost of the object and object.path be the path of the object.  Also, let Cost(i,j) indicate the cost of going from node i to node j.

1. Add an object to an initially empty priority queue, where object.cost=0 and object.path=startNode

2.  While the top object in the priority queue does not contain a path that includes endNode do
3.  	Pop the top item off the priority queue and store it as the variable current
4.	Let n be the last node in current.path
5.	For each neighbor j of n (i.e., Cost(n,j) > 0), add an object obj to the priority queue in which obj.cost = current.cost+Cost(n,j) and obj.path = concat(current.path, j)

## Implementation Notes

The simplest way of implementing the above algorithm is to use a priority queue.  Here’s a few hints to help you use priority queues in C++:

### Hint 1
In this priority queue, you will store custom path objects.  In my code, I defined these path objects as follows:

struct aPath {
    int cost;
    queue<int> path;
    bool operator() (aPath const& p1, aPath const& p2) {
        return p1.cost > p2.cost;
    }
};


Note that a struct in C++ is essentially a class.  So a variable of type aPath has two fields: cost and path.  The cost variable stores the cost of navigating the partial path specified by path, which is a queue defining the order of nodes to be traversed.  Additionally, the struct overloads the operator function.  This function tells us how to compare 2 paths p1 and p2.  The priority queue will call this function to determine which of two paths has the least cost as it decides which item should be at the top/front of the priority queue.

### Hint 2
An implementation of priority queues is provided in C++’s standard library.  To use it, you need to include <queue> and using namespace std;

To define a priority queue variable of type int in C++, you simply use the following code:

priority_queue<int> myPriorityQueue;

However, when you build it using a custom type, the syntax becomes a little more complex.  To declare a priority queue that inserts objects of type aPath (see above), you would declare your priority queue as follows:

priority_queue<aPath, vector<aPath>, aPath> myPriorityQueue;

This tells the compiler that you want to store objects of type aPath in the priority queue (this is indicated by the first parameter in the carrots) and that the way of comparing the priority of objects of type aPath is given in the aPath struct/class (this is indicated by the third parameter).  The second parameter tells the compile the type of container to use in implementing the priority queue – you don’t need to worry about understanding this right now.

### Hint 3
Remember that, in C++, the function top() returns the item on the priority queue with the highest priority.  It does not remove that item from the priority queue.  To remove the item with the highest priority, you need to call the function pop().  Similarly, when using queues, front() returns the item in the queue that has been in the queue the longest, and pop() removes the item in the queue that has been in the queue the longest.

### Hint 4
When I implemented the algorithm described in the previous section of these lab specifications, I found it useful to be able to see what the last item was that I had added to a queue (in order to see if the path of the object I was currently considering had the endNode in it).  To do that, you can use the back() function, which returns the item that was last added to the queue.



![image](https://user-images.githubusercontent.com/5827093/130145252-731b4e7e-19c3-4ff0-87ff-540eaa9a08cb.png)
