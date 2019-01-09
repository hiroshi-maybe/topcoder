#include <vector>
#include <string>
using namespace std;

bool match(string const &p, string const &s) {
  string rest = s;
  while(rest.find(p) == 0) {
    rest = rest.substr(p.length());
  }
  return rest.length() == 0;
}

string min_pattern(string const &s) {
  for (int i=0; i<s.size(); i+=1) {
    string pat = s.substr(0,i+1);
    if (match(pat, s)) return pat;
  }
  return s;
}

class InfiniteString {
public:
    string equal(string const &s,
                 string const &t) {
      
      string s_pat = min_pattern(s);
      string t_pat = min_pattern(t);
      return s_pat==t_pat ? "Equal" : "Not equal";
    }
};
