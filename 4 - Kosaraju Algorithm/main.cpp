//
//  main.cpp
//  4 - Kosaraju Algorithm
//
//  Created by Justin on 11/18/17.
//  Copyright © 2017 Justin. All rights reserved.
//

#include <iostream>
#include "Graph.h"
using namespace std;

int main() {
   string  filePath("/Users/justin/Desktop/SCC.txt");
   string filePath2("/Users/justin/Desktop/SCCtest.txt");
   string filePath3("/Users/justin/Desktop/SCCtest2.txt");
   string filePath4("/Users/justin/Desktop/SCCtest3.txt");

   Graph<int> myTree(filePath2);
   myTree.DFSloop(REVERSED);
   myTree.rearrangePtrs();
   myTree.setAllUnexplored();
   vector<int> SCCsizes = myTree.DFSloop(NOT_REVERSED);
   for (int size : SCCsizes)
      cout << size << " ";
   return 0;
}
