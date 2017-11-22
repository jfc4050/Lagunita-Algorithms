//
//  VertexPtrNode.h
//  4 - Kosaraju Algorithm
//
//  Created by Justin on 11/21/17.
//  Copyright © 2017 Justin. All rights reserved.
//

#ifndef VertexPtrNode_h
#define VertexPtrNode_h

#include "Vertex.h"

template <class Comparable> class VertexPtrTree;


template <class Comparable>
class VertexPtrNode
{
   friend class VertexPtrTree<Comparable>;
protected:
   Vertex<Comparable>* vertex;
   VertexPtrNode<Comparable>* lftChild;
   VertexPtrNode<Comparable>* rtChild;
public:
   VertexPtrNode(const Comparable& initVal) :
      vertex(new Vertex<Comparable>(initVal)),
      lftChild(nullptr),
      rtChild(nullptr) { };
   
   Vertex<Comparable>* getVertexPtr() const { return vertex; }
   
   bool operator<(const VertexPtrNode<Comparable>& rhs) const { return vertex->data < rhs.vertex->data; }
   bool operator<(const Comparable& rhs) const { return vertex->data < rhs; }
   bool operator>(const VertexPtrNode<Comparable>& rhs) const { return vertex->data > rhs.vertex->data; }
   bool operator>(const Comparable& rhs) const { return vertex->data > rhs; }
};

#endif /* VertexPtrNode_h */
