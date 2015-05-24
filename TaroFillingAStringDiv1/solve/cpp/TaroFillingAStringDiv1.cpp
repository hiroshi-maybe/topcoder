#include <vector>
#include <string>

// http://peroon.hatenablog.com/entry/20091123/1258966199

//repetition
//------------------------------------------
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

//typedef
//------------------------------------------
typedef long long LL;

//debug
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;

using namespace std;

class TaroFillingAStringDiv1 {
public:
    int getNumber(int N,
                  vector<int> const &position,
                  string const &value) {

      LL res = 1;
      REP (i1, position.size()) {
	int neib = N + 1;
	int neib_i = N;
	int p1 = position[i1];
	REP (i2, position.size()) {
	  int p2 = position[i2];
	  if (p2 > p1 && p2 < neib) {
	    neib = p2;
	    neib_i = i2;
	  }
	}

	if (neib > N) continue;

	int offset = neib - p1;
	bool equal = value[i1] == value[neib_i];

	if (offset > 0 && ((!(offset % 2) && !equal) || (offset % 2 && equal))) {
	  res = (res * offset) % 1000000007;
	}
      }
      return res;
    }
};
