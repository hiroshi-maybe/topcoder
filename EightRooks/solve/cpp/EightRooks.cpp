#include <vector>
#include <string>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

class EightRooks {
public:
    string isCorrect(vector<string> const &board) {
      int rows[8] = {0, 0, 0, 0, 0, 0, 0, 0};
      int cols[8] = {0, 0, 0, 0, 0, 0, 0, 0};

      REP(i, 8) {
	string row = board[i];
	REP(j, 8) {
	  if (row[j]=='R') {
	    rows[i] += 1;
	    cols[j] += 1;
	  }
	}
      }

      for (int row : rows) {
	if (row != 1) return "Incorrect";
      }
      for (int col : cols) {
	if (col != 1) return "Incorrect";
      }
      return "Correct";
    }
};
