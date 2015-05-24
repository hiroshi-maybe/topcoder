#include <vector>
#include <string>
using namespace std;

#define dump(x)  cerr << #x << " = " << (x) << endl;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

class EightRooks {
public:
    string isCorrect(vector<string> const &board) {
      int rows = 0;
      int cols = 0;

      REP(i, 8) {
	string row = board[i];
	REP(j, 8) {
	  if (row[j]=='R') {
	    rows += 1 << i;
	    cols += 1 << j;
	  }
	}
      }

      if (rows != 255) return "Incorrect";
      if (cols != 255) return "Incorrect";
      return "Correct";
    }
};
