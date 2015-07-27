#include <vector>
#include <string>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

vector<int> visited;

bool isLoop(int st, int cur, vector<int> const &a) {
  if (visited[cur] == 2) return false;
  if (visited[cur] == 1) return false;
  
  visited[cur] = 1;
  if (a[cur]==st) {
    if (cur == st) return false;
    return true;
  }
  bool res = isLoop(st, a[cur], a);
  visited[cur] = 0;
  return res;
}

class PrivateD2party {
public:
    int getsz(vector<int> const &a) {
      int loop=0;
      int n = a.size();
      visited = vector<int>(n, 0);
      REP(i, n) {
	visited[i] = 0;
	if (isLoop(i, i, a)) {
	  loop+=1;
	}
	visited[i] = 2;
      }
      return n-loop;
    }
};
