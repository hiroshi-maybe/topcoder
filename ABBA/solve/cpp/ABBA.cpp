#include <vector>
#include <string>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

string append(string str) {
  return str + 'A';
}

string reverse(string str) {
  std::string rev(str);
  std::reverse(rev.begin(), rev.end());
  return rev + 'B';
}

bool dfs(string const &current, string const &target, int aNum, int bNum) {
  if (aNum < 0 || bNum < 0) return false;
  if (current.length() == target.length()) { return current == target; }
  if (dfs(append(current), target, aNum-1, bNum)) { return true; }
  return dfs(reverse(current), target, aNum, bNum-1);
}

class ABBA {
public:
    string canObtain(string const &initial,
                     string const &target) {
      int aNum = 0; int bNum = 0;
      REP(i, target.length()) {
	if (target[i] == 'A') aNum+=1;
	if (target[i] == 'B') bNum+=1;
      }
      REP(i, initial.length()) {
	if (initial[i] == 'A') aNum-=1;
	if (initial[i] == 'B') bNum-=1;
      }      
      
      return dfs(initial, target, aNum, bNum) ? "Possible" : "Impossible";
    }
};
