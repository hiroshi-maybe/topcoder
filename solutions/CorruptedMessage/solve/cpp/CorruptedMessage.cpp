#include <vector>
#include <string>
#include <map>

using namespace std;

class CorruptedMessage {
public:
    string reconstructMessage(string const &s,
                              int k) {

      char alphabet[] =  {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
      
      char ok;
      map<char, int> charCount;
      for (char c : s) {
	if (charCount.find(c) != charCount.end()) {
	  charCount.insert(pair<char,int>(c,0));
	}
	charCount[c] += 1;
      }

      int strlen = s.length();
      int goodCount = strlen - k;
      char notFound;
      for (char c : alphabet) {
	if (charCount.find(c) != charCount.end()) {
	  if (charCount[c] == goodCount) return string(strlen, c);
	} else {
	  if (!notFound) notFound = c;
	}
      }
      return string(strlen, notFound);
    }
};
