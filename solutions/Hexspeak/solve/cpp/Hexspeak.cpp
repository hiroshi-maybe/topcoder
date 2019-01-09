#include <vector>
#include <string>
#include <locale>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

class Hexspeak {
public:
    string decode(int64 ciphertext) {
      std::stringstream stream;
      stream << std::hex << ciphertext;
      std::string res( stream.str() );

      REP(i, res.length()) {
	res[i] = toupper(res[i]);
	if (res[i] == '0') res[i] = 'O';
	if (res[i] == '1') res[i] = 'I';
	if (res[i] >= '2' && res[i] <= '9') return "Error!";
      }
      return res;
    }
};
