#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define SORT(c) sort((c).begin(),(c).end())

int dist(int x1, int y1, int x2, int y2) {
  return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

class IsItASquare {
public:
    string isSquare(vector<int> const &x,
                    vector<int> const &y) {
      vector<int> lines = {
	dist(x[0],y[0],x[1],y[1]),
	dist(x[1],y[1],x[2],y[2]),
	dist(x[2],y[2],x[3],y[3]),
	dist(x[3],y[3],x[0],y[0]),
      	dist(x[0],y[0],x[2],y[2]),
      	dist(x[1],y[1],x[3],y[3])};

      SORT(lines);
      if (lines[0]==lines[1]
	  && lines[1]==lines[2]
	  && lines[2]==lines[3]
	  && lines[4]==lines[5]) {
	return "It's a square";
      } else {
	return "Not a square";
      }
    }
};
