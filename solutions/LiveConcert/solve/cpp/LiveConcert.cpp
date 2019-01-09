#include <vector>
#include <string>
#include <map>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

#define EXIST(s,e) ((s).find(e)!=(s).end())
#define DEFAULT(s,e,x) if (!EXIST(s, e)) { s[e]=x; }
#define ITER(i,s) for(auto i=s.begin(); i!=s.end(); i++)

class LiveConcert {
public:
    int maxHappiness(vector<int> const &h,
                     vector<string> const &s) {
      map<string,int> hap;
      
      REP(i, h.size()) {
	auto name = s[i];
	DEFAULT(hap, name, 0);
	hap[name] = max(hap[name], h[i]);
      }

      int res = 0;
      ITER(i, hap) {
	res += i->second;
      }
      return res;
    }
};
