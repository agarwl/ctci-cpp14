/******Possible Invariants**********/
/*
a[lo] <  target <  a[hi]
a[lo] <= target <  a[hi]
a[lo] <  target <= a[hi]
a[lo] <= target <= a[hi]

You'll usually see the last one because it's the easiest to explain and 
doesn't involve tricky initialization with out-of-range array indices, which the others do.
Now there is a reason to use an invariant like  a[lo] < target <= a[hi]. 
If you want always to find the first of a repeated series of the target, this invariant
will do it O(log n) time. When hi - lo == 1, hi points to the first occurrence of the target.
*/
#include <bits/stdc++.h>
using namespace std;

#define NOT_FOUND -1

int find(int target, int *a, int size) {
  // Establish invariant: a[lo] < target <= a[hi] || target does not exist
  // We assume a[-1] contains an element less than target. But since it is never
  // accessed, we don't need a real element there.
  int lo = -1, hi = size - 1;
  while (hi - lo > 1) {
    // mid == -1 is impossible because hi-lo >= 2 due to while condition
    int mid = lo + (hi - lo) / 2;  // or (hi + lo) / 2 on 32 bit machines
    if (a[mid] < target)
      lo = mid; // a[mid] < target, so this maintains invariant
    else
      hi = mid; // target <= a[mid], so this maintains invariant
  }
  // if hi - lo == 1, then hi must be first occurrence of target, if it exists.
  return hi > lo && a[hi] == target ? hi : NOT_FOUND;
}

int main()
{
  return 0;
}