#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

//#define SORT(c) sort((c).begin(),(c).end())
//bool compare(int i,int j){return (i>j);}

class FilipTheFrog {
public:
    int countReachableIslands(vector<int> const &positions,
                              int L) {
      int start = positions[0];
      sort(positions.rbegin(), positions.rend());

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
      for (int i=positions.size()-1; i>0; --i) {
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
