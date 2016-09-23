#include <vector>
#include <string>
#include <algorithm> // max,min
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n) FOR(i,0,n)
#define SORT(c) sort((c).begin(),(c).end())

class DivisibleSetDiv2 {
public:
  string isPossible(vector<int> &b) {
    SORT(b);

    vector<int> a;
    REP(i, b.size()) { a.push_back(1); }
    int sum = b.size();
    while (true) {

      REP(i, b.size()) {
	if (a[i] * b[i] < sum) {
	  a[i]+=1; sum+=1;
	  if (a[i]==1000) return "Impossible";

	  break;
	}

	if (i==b.size()-1) { return "Possible"; }
      }
	
    }
    
    return "Impossible";
  }
};
