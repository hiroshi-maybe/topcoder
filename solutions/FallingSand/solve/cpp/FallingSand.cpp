#include <vector>
#include <string>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

#define dump(x)  cerr << #x << " = " << (x) << endl;

class FallingSand {
public:
    vector<string> simulate(vector<string> &board) {
      int len = board.size();
      REP(j,board[0].size()) {
	int sandCount = 0;
	REP(i,len) {
	  char c = board[i][j];
	  if (c == 'o') {
	    sandCount+=1;
	    board[i][j] = '.';
	  }
	  if (c == 'x' || i == len-1) {
	    if (sandCount>0) {
	      int l = c == 'x' ? 1 : 0;
	      REP(k,sandCount) board[i-k-l][j]='o';
	      sandCount=0;
	    }
	  }
	}
      }
      return board;
    }
};
