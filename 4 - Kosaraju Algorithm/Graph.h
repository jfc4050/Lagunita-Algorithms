//
//  Graph.h
//  4 - Kosaraju Algorithm
//
//  Created by Justin on 11/18/17.
//  Copyright © 2017 Justin. All rights reserved.
//

#ifndef Graph_h
#define Graph_h

#include <vector>
#include <fstream>
#include <cassert>
#include "SortableVertPtr.h"
#include "VertexPtrTree.h"
#include "Vertex.h"
#include "quickSort.h"
using namespace std;

enum order { REVERSED, NOT_REVERSED };


template <class Comparable>
class Graph
{
protected:
   VertexPtrTree<Comparable> vertexPtrSet;
   vector<SortableVertPtr<Comparable>> sortableVertPtrs;
public:
   Graph(const string& filePath);
   
   pair<Vertex<Comparable>*, bool> addVertex(const Comparable& vertData);
   void addToVertPtrs(Vertex<Comparable>* ptrIn);
   void addEdge(Vertex<Comparable>*& source, Vertex<Comparable>*& dest) const;
   
   vector<int> DFSloop(int order) const;
   void rearrangePtrs() { quickSort(sortableVertPtrs); }
   void setAllUnexplored() const;
protected:
   void DFSrecurse(Vertex<Comparable>* vertPtr, Vertex<Comparable>* sourcePtr, int& finishTime, int& SCCsize) const;
   void DFSrecurseRev(Vertex<Comparable>* vertPtr, Vertex<Comparable>* sourcePtr, int& finishTime, int& SCCsize) const;
};


#endif /* Graph_h */


template <class Comparable>
Graph<Comparable>::Graph(const string& filePath) {
   ifstream inFile(filePath);
   int source, dest;
   while(inFile.good()) {
      if( inFile >> source >> dest ) {
         pair<Vertex<Comparable>*, bool> src = addVertex(source);
         pair<Vertex<Comparable>*, bool> dst = addVertex(dest);
         
         Vertex<Comparable>* srcPtr = src.first;
         Vertex<Comparable>* dstPtr = dst.first;
         bool addedSrc = src.second;
         bool addedDst = dst.second;
         
         addEdge(srcPtr, dstPtr);
         
         if (addedSrc) addToVertPtrs(srcPtr);
         if (addedDst) addToVertPtrs(dstPtr);
      }
   }
}


template <class Comparable>
pair<Vertex<Comparable>*, bool> Graph<Comparable>::addVertex(const Comparable& vertData) {
   pair<VertexPtrNode<Comparable>*, bool> result = vertexPtrSet.insertNode(vertData);
   VertexPtrNode<Comparable>* vertNodePtr = result.first;
   bool insertedVert                      = result.second;
   return make_pair(vertNodePtr->getVertexPtr(), insertedVert);
}


template <class Comparable>
void Graph<Comparable>::addEdge(Vertex<Comparable>*& source, Vertex<Comparable>*& dest) const {
   (source)->addToAdjacencyList(dest);
   (dest)->addToRevAdjacencyList(source);
}


template <class Comparable>
void Graph<Comparable>::addToVertPtrs(Vertex<Comparable>* ptrIn) {
   SortableVertPtr<Comparable> newPtr(ptrIn);
   sortableVertPtrs.push_back(newPtr);
}


template <class Comparable>
void Graph<Comparable>::DFSrecurse(Vertex<Comparable>* vertPtr, Vertex<Comparable>* sourcePtr, int& finishTime, int& SCCsize) const {
   vertPtr->setExplored(true);
   vertPtr->setLeader(sourcePtr);
   for ( Vertex<Comparable>* adjVertex : vertPtr->getAdjacencyList() ) {
      if (!adjVertex->isExplored()) {
         SCCsize++;
         DFSrecurse(adjVertex, sourcePtr, finishTime, SCCsize);
      }
   }
   finishTime++;
   vertPtr->setFinishTime(finishTime);
}


template <class Comparable>
void Graph<Comparable>::DFSrecurseRev(Vertex<Comparable>* vertPtr, Vertex<Comparable>* sourcePtr, int& finishTime, int& SCCsize) const {
   vertPtr->setExplored(true);
   vertPtr->setLeader(sourcePtr);
   for ( Vertex<Comparable>* adjVertex : vertPtr->getRevAdjacencyList() ) {
      assert(adjVertex != nullptr);
      if (!adjVertex->isExplored()) {
         SCCsize++;
         DFSrecurseRev(adjVertex, sourcePtr, finishTime, SCCsize);
      }
   }
   finishTime++;
   vertPtr->setFinishTime(finishTime);
}


template <class Comparable>
vector<int> Graph<Comparable>::DFSloop(int order) const {
   int finishTime = 0;
   Vertex<Comparable>* sourcePtr = nullptr;
   vector<int> SCCsizes{};
   for (SortableVertPtr<Comparable> vertPtr : sortableVertPtrs) {
      if (!vertPtr->isExplored()) {
         int SCCsize = 1;
         sourcePtr = vertPtr.getPointee();
         switch (order) {
            case REVERSED:
               DFSrecurseRev(sourcePtr, sourcePtr, finishTime, SCCsize);
               break;
            case NOT_REVERSED:
               DFSrecurse(sourcePtr, sourcePtr, finishTime, SCCsize);
               break;
         }
         SCCsizes.push_back(SCCsize);
      }
   }
   return SCCsizes;
}


template <class Comparable>
void Graph<Comparable>::setAllUnexplored() const {
   for (SortableVertPtr<Comparable> vertPtr : sortableVertPtrs) {
      vertPtr->setExplored(false);
   }
}

