#include <vector>
#include <algorithm>
#include <string>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dumpAR(ar,n) REP(i,(n)) { cerr << ar[i] << ','; } cerr << endl;

// Combination generator
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

// Floyd-Warshall
vector<vector<int>> floydWarshall(vector<vector<int>> dist, int edgeNum) {
  for (int k = 0; k < edgeNum; k++) {
    for (int i = 0; i < edgeNum; i++) {
      for (int j = 0; j < edgeNum; j++) {
	dist[i][j] = std::min( dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
  return dist;
}

class BridgeBuildingDiv2 {
public:
    int minDiameter(vector<int> const &a,
                    vector<int> const &b,
                    int K) {
      int n = a.size() + 1;
      int INF = 1000000;
      auto combs = combination(K, n);

      int minDist=INF;
      
      REP(x, combs.size()) {
	vector<int> br = combs[x];
	vector<vector<int>> dist(2*n, vector<int>(2*n, INF));

	// bridge dist
	REP(i, K) {
	  dist[br[i]][br[i]+n] = dist[br[i]+n][br[i]] = 0;	  
	}

	REP(i, n-1) {
	  // top
	  dist[i][i+1] = dist[i+1][i] = a[i];
	  // bottom
	  dist[i+n+1][i+n] = dist[i+n][i+n+1] = b[i];
	}
	dist = floydWarshall(dist, n*2);

	int maxDist=0;
	REP(i, n*2) FOR(j, i+1, n*2) {
	  maxDist = max(maxDist, dist[i][j]);
	}
	minDist = min(minDist, maxDist);
      }
      
      return minDist;
    }
};
