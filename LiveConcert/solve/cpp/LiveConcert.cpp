#include <vector>
#include <string>
#include <map>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

#define EXIST(s,e) ((s).find(e)!=(s).end())

class LiveConcert {
public:
    int maxHappiness(vector<int> const &h,
                     vector<string> const &s) {
      map<string,int> hap;
      
      REP(i, h.size()) {
	auto name = s[i];
	if (!EXIST(hap, name)) {
	  hap[name] = 0;
	}
	hap[name] = max(hap[name], h[i]);
      }

      int res = 0;
      for (auto i = hap.begin() ; i != hap.end() ; i++ ) {
	 res += i->second;
      }

      return res;
    }
};
