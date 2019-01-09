#include <vector>
#include <string>
using namespace std;

class Initials {
public:
  string getInitials(string const &name) {
    string s = "";
    auto it = name.begin();
    s += *it;
    while (it != name.end()) {
      if (*it == ' ') {
	it++;
	s += *it;
      }
      it++;
    }

    return s;
  }
};
