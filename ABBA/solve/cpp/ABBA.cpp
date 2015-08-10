#include <vector>
#include <string>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

string rem(string str) {
  return str + 'A';
}

string reverse(string str) {
  std::string rev(str);
  std::reverse(rev.begin(), rev.end());
  return rev;
}

bool dfs(string const &current, string const &initial) {
    int length = current.length();
  if (length == initial.length()) { return current == initial; }

  char last = current[length-1];
  string sub = current.substr(0, length-1);
  
  if (last == 'A') { return dfs(sub, initial); }
  return dfs(reverse(sub), initial);
}

class ABBA {
public:
    string canObtain(string const &initial,
                     string const &target) {
      return dfs(target, initial) ? "Possible" : "Impossible";
    }
};
