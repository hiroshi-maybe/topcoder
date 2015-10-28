#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

int line(int x1, int y1, int x2, int y2) {
  return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

class IsItASquare {
public:
    string isSquare(vector<int> const &x,
                    vector<int> const &y) {
      int orders[] = {0,1,2,3};
      do {
	int linelen = -1;
	bool samelen = true;
	REP(i, 4) {
	  int order1 = orders[i];
	  int order2 = i!=3 ? orders[i+1] : orders[0];
	  if (linelen == -1) {
	    linelen = line(x[order1],y[order1],x[order2],y[order2]);
	    continue;
	  }			 
	  int len = line(x[order1],y[order1],x[order2],y[order2]);
	  if (len != linelen) {
	    samelen = false;
	    break;
	  }
	}
	if (samelen) return "It's a square";
      } while ( std::next_permutation(orders,orders+4) );
      return "Not a square";
    }
};
