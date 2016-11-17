#include <vector>
#include <string>

using namespace std;

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define ROF(i,a,b) for(int i=(a);i>=(b);--i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
#define REPS(i,arr)  for(int i=0; i<(arr).size(); ++i)

#define dump(x)  cout << #x << " = " << (x) << endl;
#define dump2(x,y)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cout << endl;

int maskToIdx[1000001];
int alice[1000001];
int bob[1000001];

class PartisanGame {
public:
  string getWinner(int n,
                   vector<int> const &a,
                   vector<int> const &b) {
    memset(maskToIdx, 0, sizeof(maskToIdx));
    alice[0] = false;
    bob[0] = false;
    for(int i = 1; i <= n; i++) {
      alice[i] = false;
      bob[i] = false;
      for(int j = 0; j < a.size(); j++) {
	if(a[j] <= i && !bob[i-a[j]]) {
	  alice[i] = true;
	}
      }
      for(int j = 0; j < b.size(); j++) {
	if(b[j] <= i && !alice[i-b[j]]) {
	  bob[i] = true;
	}
      }
      //      if (i<10) { dump(i); dump2(alice[i],bob[i]);}
      if(i > 100) {
	int curMask = 0;
	for(int j = 0; j < 5; j++) {
	  curMask = curMask * 2 + alice[i-j];
	  curMask = curMask * 2 + bob[i-j];
	}
	if(maskToIdx[curMask] > 0) {
	  int cycleLen = i - maskToIdx[curMask];
	  int fastForward = max(0, (n - i) / cycleLen - 2);
	  n -= fastForward * cycleLen;
	  dump(n);
	} else {
	  maskToIdx[curMask] = i;
	}
      }
    }
    return (alice[n] ? "Alice" : "Bob");}
};
