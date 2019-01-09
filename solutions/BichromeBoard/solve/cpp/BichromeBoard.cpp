#include <vector>
#include <string>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

#define dump(x)  cerr << #x << " = " << (x) << endl;

class BichromeBoard {
public:
    string ableToDraw(vector<string> const &board) {
      // start with W
      bool res1 = true;
      REP(i, board.size()) {
	REP(j, board[i].length()) {
	  char c = board[i][j];
	  if ((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1)) {
	    if (c == 'B') {
	      res1 = false;
	      break;
	    }
	  }
	  if ((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0)) {
	    if (c == 'W') {
	      res1 = false;
	      break;
	    }
	  }
	}
	if (!res1) break;
      }

      // start with B
      bool res2 = true;
      REP(i, board.size()) {
	REP(j, board[i].length()) {
	  char c = board[i][j];
	  if ((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1)) {
	    if (c == 'W') {
	      res2 = false;
	      break;
	    }
	  }
	  if ((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0)) {
	    if (c == 'B') {
	      res2 = false;
	      break;
	    }
	  }	  
	}
	if (!res2) break;
      }

      return res1 || res2 ? "Possible" : "Impossible";
    }
};
