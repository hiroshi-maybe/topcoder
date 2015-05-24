#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

#define SORT(c) sort((c).begin(),(c).end())

class FilipTheFrog {
public:
    int countReachableIslands(vector<int> &positions,
                              int L) {
      int start = positions[0];
      SORT(positions);

      int res = 1;
      
      // forward
      int current = start;
      for (int p : positions) {
	if (p <= start) continue;
	int dif = p - current;
	if (dif > L) break;
	++res;
	current = p;
      }

      // backward
      current = start;
      for (int i=positions.size()-1; i>=0; --i) {
	int p = positions[i];
	if (p >= start) continue;
	int dif = current - p;
	if (dif > L) break;
	++res;
	current = p;
      }

      return res;
    }
};
