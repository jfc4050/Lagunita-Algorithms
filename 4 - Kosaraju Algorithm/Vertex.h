//
//  Vertex.h
//  4 - Kosaraju Algorithm
//
//  Created by Justin on 11/21/17.
//  Copyright © 2017 Justin. All rights reserved.
//

#ifndef Vertex_h
#define Vertex_h

#include <set>
using namespace std;

template <class Comparable> class VertexPtrNode;
template <class Comparable> class SortableVertPtr;


template <class Comparable>
class Vertex
{
   friend class VertexPtrNode<Comparable>;
   friend class SortableVertPtr<Comparable>;
protected:
   Comparable data;
   set<Vertex*> adjacencyList;
   set<Vertex*> revAdjacencyList;
   bool explored;
   int finishTime;
   Vertex<Comparable>* leader;
public:
   Vertex(Comparable dataIn) :
      data(dataIn),
      adjacencyList(),
      revAdjacencyList(),
      explored(false),
      finishTime(-1),
      leader(nullptr) { };
   
   void addToAdjacencyList(Vertex* dest) { adjacencyList.insert(dest); }
   const set<Vertex*>& getAdjacencyList() const { return adjacencyList; }
   void addToRevAdjacencyList(Vertex* source) { revAdjacencyList.insert(source); }
   const set<Vertex*>& getRevAdjacencyList() const { return revAdjacencyList; }
   
   bool isExplored() const { return explored; }
   void setExplored(bool exploredStatus) { explored = exploredStatus; }
   
   void setFinishTime(int newTime) { finishTime = newTime; }
   
   void setLeader(Vertex<Comparable>* newLeader) { leader = newLeader; }
   
   bool operator<(const Vertex<Comparable>& rhs) const { return data < rhs.data; }
   bool operator<(const Comparable& rhs) const { return data < rhs; }
};

#endif /* Vertex_h */
