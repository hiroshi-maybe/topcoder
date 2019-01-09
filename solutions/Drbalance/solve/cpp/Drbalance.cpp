#include <vector>
#include <string>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

int score(vector<int> const &pref) {
  int res = 0;
  REP(i, pref.size()) {
    res += pref[i] < 0 ? 1 : 0;
  }
  return res;
}

class Drbalance {
public:
    int lesscng(string &s,
                int k) {
      vector<int> pref(s.size());
      REP(i, s.size()) {
	int prev = i>0 ? pref[i-1] : 0;
	pref[i] = s[i] == '-' ? prev - 1 : prev + 1;
      }
      int res = 0;
      while (int x = score(pref) > k) {
	REP(i, s.size()) {
	  if (s[i] == '-') {
	    s[i] = '+';
	    FOR(j, i, pref.size()) {
	      pref[j] += 2;
	    }
	    res += 1;
	    break;
	  }
	}
      }
      
      return res; 
    }
};
