//
//  SortableVertPtr.h
//  4 - Kosaraju Algorithm
//
//  Created by Justin on 11/21/17.
//  Copyright © 2017 Justin. All rights reserved.
//

#ifndef SortableVertPtr_h
#define SortableVertPtr_h

#include "Vertex.h"

enum sortKey { BY_DATA, BY_FINISHTIME };

template <class Comparable>
class SortableVertPtr
{
protected:
   Vertex<Comparable>* pointee;
   static int sortKey;
public:
   SortableVertPtr(Vertex<Comparable>* vertexPtr) : pointee(vertexPtr) { };
   
   Vertex<Comparable>* getPointee() const { return pointee; }
   
   Vertex<Comparable>* operator->() { return &*pointee; }
   Vertex<Comparable>& operator*() { return *pointee; }
   bool operator<(const SortableVertPtr<Comparable>& rhs);
   bool operator<(const Comparable& rhs) { return pointee->data < rhs; }
};

#endif /* SortableVertPtr_h */


template <class Comparable>
int SortableVertPtr<Comparable>::sortKey = BY_FINISHTIME;


template <class Comparable>
bool SortableVertPtr<Comparable>::operator<(const SortableVertPtr<Comparable>& rhs) {
   switch (sortKey) {
      case BY_DATA:
         return pointee->data < rhs.pointee->data;
      case BY_FINISHTIME:
         return pointee->finishTime < rhs.pointee->finishTime;
   }
   return false;
}
