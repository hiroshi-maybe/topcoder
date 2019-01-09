#include <vector>
#include <string>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

int match(string const &s, char c, int n) {
  int count = 0;
  string x = string(n, c);
  REP(i, s.length()-n+1) {
    if (s.substr(i).find(x)==0) count+=1;
  }
  return count;
}

class SquareScoresDiv2 {
public:
    int getscore(string const &s) {
      int count=0;
      for (char c = 'a'; c <= 'z'; c+=1) {
	if (s.find(c)==std::string::npos) continue;
	FOR(n, 1, s.length()+1) {
	  count += match(s, c, n);
	}
      }

      return count;
    }
};
