#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#define SORT(c) sort((c).begin(),(c).end())
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

class CombiningSlimes {
public:
    int maxMascots(vector<int> &a) {
      SORT(a);

      int res = 0;
      int prevw = 0;
      REP(i, a.size()) {
	res += prevw * a[i];
	prevw += a[i];
      }
      return res;
    }
};
