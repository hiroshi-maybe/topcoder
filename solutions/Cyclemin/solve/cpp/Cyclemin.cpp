#include <vector>
#include <string>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

class Cyclemin {
public:
    string bestmod(string const &s,
                   int k) {
      string sm = s;
      
      REP(i,s.size()) {
	string s1 = s.substr(i) + s.substr(0, i);
	int y = k;
	REP(j, s1.size()) {
	  if (s1[j]!='a' && y > 0) {
	    s1[j] = 'a';
	    y--;
	  }
	}
	sm = s1 < sm ? s1 : sm;
      }

      return sm;
    }
};
