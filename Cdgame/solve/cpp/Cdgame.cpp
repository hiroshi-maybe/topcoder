#include <vector>
#include <string>
#include <set>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

class Cdgame {
public:
    int rescount(vector<int> const &a,
                 vector<int> const &b) {
      set<int> res;
      int suma = 0;
      int sumb = 0;
      REP(i,a.size()) suma+=a[i];
      REP(i,b.size()) sumb+=b[i];

      REP(i, a.size()) {
	REP(j, b.size()) {
	  int sa = suma;
	  int sb = sumb;
	  sa = sa - a[i]+b[j];
	  sb = sb - b[j]+a[i];
	  res.insert(sa*sb);
	}
      }
      return res.size();
    }
};
