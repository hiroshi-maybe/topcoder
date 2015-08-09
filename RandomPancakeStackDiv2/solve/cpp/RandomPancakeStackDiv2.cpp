#include <vector>
#include <string>
using namespace std;

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

double dp[100][100];

double expect(int n, int j, vector<int> const &d) {
  double res = d[j];
  int size = d.size();
  REP(i, j) {
    res += (1.0 / (double)n) * expect(n-1, i, d);
  }
  return res;
}

class RandomPancakeStackDiv2 {
public:
    double expectedDeliciousness(vector<int> const &d) {
      int n = d.size();
      double res = 0.0;
      REP(i, n) {
	res += (1.0 / (double)n) * expect(n-1, i, d);
      }
      return res;
    }
};
