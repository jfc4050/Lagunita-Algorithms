//
//  VertexPtrTree.h
//  4 - Kosaraju Algorithm
//
//  Created by Justin on 11/21/17.
//  Copyright © 2017 Justin. All rights reserved.
//

#ifndef VertexPtrTree_h
#define VertexPtrTree_h

#include "VertexPtrNode.h"
using namespace std;

template <class Comparable>
class VertexPtrTree
{
protected:
   VertexPtrNode<Comparable>* mRoot;
public:
   VertexPtrTree() :
      mRoot(nullptr) { };
   pair<VertexPtrNode<Comparable>*, bool> insertNode(const Comparable& nodeData) { return insertRecursive(nodeData, mRoot); }
protected:
   pair<VertexPtrNode<Comparable>*, bool> insertRecursive(const Comparable& nodeData, VertexPtrNode<Comparable>*& root);
};

#endif /* VertexPtrTree_h */


template <class Comparable>
pair<VertexPtrNode<Comparable>*, bool> VertexPtrTree<Comparable>::insertRecursive(const Comparable& nodeData, VertexPtrNode<Comparable>*& root) {
   if (root == nullptr) {
      root = new VertexPtrNode<Comparable>(nodeData);
      return make_pair(root, true);
   } else if (*root < nodeData) {
      return insertRecursive(nodeData, root->rtChild);
   } else if (*root > nodeData) {
      return insertRecursive(nodeData, root->lftChild);
   }
   return make_pair(root, false);
}
