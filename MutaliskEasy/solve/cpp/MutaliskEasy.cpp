#include <vector>
#include <string>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

#define dump(x)  cerr << #x << " = " << (x) << endl;

bool defeated(vector <int> const &x, vector <int> const &org) {
  REP(i, x.size()) {
    if (x[i] < org[i]) return false;
  }
  return true;
}

vector<vector<vector<int>>> attack_pat = {
  {{9}},
  {{9,3},{3,9}},
  {{9,3,1},{9,1,3},{1,3,9},{1,9,3},{3,1,9},{3,9,1}}
};

class MutaliskEasy {
public:
    int minimalAttacks(vector<int> const &x) {
      auto size = x.size();
      auto attacks = attack_pat[x.size()-1];
      vector<vector<int>> history = attacks;

      int c = 0;
      while(1) {
	dump(c);
	vector<vector<int>> next_history;
	REP(i, history.size()) {
	  auto c_stat = history[i];
	  if (defeated(c_stat, x)) return c+1;
	  REP(j, attacks.size()) {
	    auto attack = attacks[j];
	    auto stat = c_stat;
	    REP(k, attack.size()) {
	      stat[k] += attack[k];
	      //	    cerr << stat[k] << ',';
	    }
	    //	    	    cerr << endl;
	    next_history.push_back(stat);
	  }
	}
	history = next_history;
	c+=1;
      }
    }
};
