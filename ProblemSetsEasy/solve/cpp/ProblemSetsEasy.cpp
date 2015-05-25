#include <vector>
#include <string>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

int valid(int x,
      int E,
      int EM,
      int M,
      int MH,
      int H) {

  int maxa = min(EM, E + EM - x);
  int maxb = min(MH, H + MH - x);

  return (M + maxa + maxb >= x);
}

class ProblemSetsEasy {
public:
    int maxSets(int E,
                int EM,
                int M,
                int MH,
                int H) {

      int res = 0;
      int start = min(min(E, M), H);
      int end = min(min(M+EM+MH,E+EM), H+MH);
      FOR(i, start, end) {
	if (valid(i, E, EM, M, MH, H)) {
	  res = i;
	}
      }

      return res;
    }
};
