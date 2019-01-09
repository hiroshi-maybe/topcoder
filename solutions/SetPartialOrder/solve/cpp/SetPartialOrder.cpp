#include <vector>
#include <string>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

class SetPartialOrder {
public:
    string compareSets(vector<int> const &a,
                       vector<int> const &b) {
      bool onlya = false;
      bool onlyb = false;
      int len = max(a.size(), b.size());
      FOR(n,1,101) {
	bool aHas = false;
	bool bHas = false;
	REP(i, len) {
	  aHas = aHas || (i<a.size() && a[i]==n);
	  bHas = bHas || (i<b.size() && b[i]==n);
	}
	if (aHas &&  bHas) { onlya = onlya||false; onlyb = onlyb||false; }
	if (aHas && !bHas) { onlya = true; }
	if (!aHas && bHas) { onlyb = true; }
      }
      if ( onlya && onlyb)  return "INCOMPARABLE";
      if (!onlya && onlyb)  return "LESS";
      if ( onlya && !onlyb) return "GREATER";
      return "EQUAL";
    }
};
