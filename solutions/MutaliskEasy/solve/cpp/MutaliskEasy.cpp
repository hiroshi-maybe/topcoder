#include <algorithm>
#include <vector>
#include <string>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define SORT(a) sort((a).begin(), (a).end());

bool defeated(vector<int> const &x) {
  REP(i, x.size()) {
    if (x[i] > 0) return false;
  }
  return true;
}

vector<vector<int>> attack_pat = {{9,3,1},{9,1,3},{1,3,9},{1,9,3},{3,1,9},{3,9,1}};

int dp[61][61][61];

vector<int> attack(vector<int> &current, vector<int> const &atk) {
  REP(i, atk.size()) {
    current[i] = max(current[i]-atk[i], 0);
  }
  return current;
}

int min_dp(vector<int> const &_current, vector<vector<int>> const &pat) {
  int res = 60;
  vector<int> current = _current;
  SORT(current);
  int dp_v = dp[current[0]][current[1]][current[2]];
  if (dp_v != 60) return dp_v;

  REP(i, 6) {
    vector<int> cur = current;
    auto post_atk = attack(cur, pat[i]);
    if (defeated(post_atk)) return 1;
    int c = min_dp(post_atk, pat);
    res = min(c, res);
  }
  return dp[current[0]][current[1]][current[2]] = res + 1;
}

class MutaliskEasy {
public:
    int minimalAttacks(vector<int> const &x) {
      REP(i,61) REP(j,61) REP(k,61) dp[i][j][k] = 60;
      vector<int> y = x;
      while(y.size() < 3) {
	y.push_back(0);
      }
      return min_dp(y, attack_pat);
    }
};
