#include <math.h>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP_(i,n)  FOR(i,0,n)
#define REP(i,n)  for((i)=0;(i)<(n);++(i))
#define SORT(a) a.sort(a.begin(), a.end());

#define dump(x)  cerr << #x << " = " << (x) << endl;

vector<vector<int>> attack_pat = {{9,3,1},{9,1,3},{1,3,9},{1,9,3},{3,1,9},{3,9,1}};

class MutaliskEasy {
public:
    int minimalAttacks(vector<int> &x) {
      int count[6];
      int mi = 20;
      while(x.size() < 3) x.push_back(0);
      REP(count[0], 16) REP(count[1], 16) REP(count[2], 16) REP(count[3], 16) REP(count[4], 16) {
	vector<int> y = x;
	REP_(i, 5) REP_(j, 3) y[j] -= count[i]*attack_pat[i][j];

	count[5] = max(0, (y[0]+2)/3);
	count[5] = max(count[5], (y[1]+8)/9);
	count[5] = max(count[5], y[2]);

	mi= min(mi, count[0]+count[1]+count[2]+count[3]+count[4]+count[5]);
      }
      return mi;
    }
};
