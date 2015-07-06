#include <vector>
using namespace std;

vector<vector<int>> combination(int k, int n) {
  vector<vector<int>> combs;
  for (int mask=0; mask<(1<<n); mask++) {
    if (__builtin_popcount(mask) == k) {
      vector<int> comb(k);
      int c=0;
      for (int i=0; i<n; i+=1) {
	if (mask & (1<<i)) {
	  comb[c]=i;
	  c++;
	}
      }
      combs.push_back(comb);
    }
  }
  return combs;
}
