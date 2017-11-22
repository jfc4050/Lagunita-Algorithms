//
//  quickSort.h
//  4 - Kosaraju Algorithm
//
//  Created by Justin on 11/21/17.
//  Copyright © 2017 Justin. All rights reserved.
//

#ifndef quickSort_h
#define quickSort_h

#include <vector>

template <class Comparable>
void insertionSort(vector<Comparable>& a, int left, int right) {
   int k;
   for( int pos = left + 1; pos <= right; pos++ )
   {
      Comparable tmp = a[pos];
      for( k = pos; k > left && tmp < a[k - 1]; k-- )
         a[k] = a[k - 1];
      a[k] = tmp;
   }
}



template <class Comparable>
inline void mySwap(Comparable& x, Comparable& y) {
   Comparable tmp = x;
   x = y;
   y = tmp;
}


template <class Comparable>
const Comparable& median3(vector<Comparable>& vectorIn, int left, int right) {
   int center = (left + right) / 2;
   if( vectorIn[center] < vectorIn[left] )
      mySwap( vectorIn[left], vectorIn[center] );
   if( vectorIn[right] < vectorIn[left] )
      mySwap( vectorIn[left], vectorIn[right] );
   if( vectorIn[right] < vectorIn[center] )
      mySwap( vectorIn[center], vectorIn[right] );
   
   mySwap(vectorIn[center], vectorIn[right - 1]);
   return vectorIn[right - 1];
}


// quickSort Internal
template <class Comparable>
void quickSort(vector<Comparable>& vectorIn,
                int left, int right,
                int recLimit = 2)
{
   if (left + recLimit <= right) {
      Comparable pivot = median3(vectorIn, left, right); // also moves pivot
      int lft = left;
      int rt  = right - 1;
      
      while(true) {
         while(vectorIn[++lft] < pivot);
         while(pivot < vectorIn[--rt]);
         if (lft < rt) mySwap(vectorIn[lft], vectorIn[rt]);
         else break;
      }
      
      mySwap(vectorIn[left], vectorIn[right-1]);
      
      quickSort(vectorIn, left, lft-1, recLimit);
      quickSort(vectorIn, lft+1, right, recLimit);
   }
   
   insertionSort(vectorIn, left, right);
}


// quickSortX Public Driver
template <class Comparable>
void quickSort(vector<Comparable>& vectorIn){
   quickSort(vectorIn, 0, vectorIn.size()-1);
}

#endif /* quickSort_h */
