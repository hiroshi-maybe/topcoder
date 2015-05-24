#include <vector>
#include <string>
using namespace std;

class TaroFillingAStringDiv1 {
public:
    int getNumber(int N,
                  vector<int> const &position,
                  string const &value) {

      if (position.size() == N) return 1;

      long res = 1;
      for (auto i1 = 0; i1 != position.size(); ++i1) {
	int neib = N + 1;
	int neib_i = N;
	int p1 = position[i1];
	for (auto i2 = 0; i2 != position.size(); ++i2) {
	  int p2 = position[i2];
	  if (p2 > p1 && p2 < neib) {
	    neib = p2;
	    neib_i = i2;
	  }
	}

	if (neib <= N) {
	  int offset = neib - p1 - 1;
	  bool equal = value.at(i1) == value.at(neib_i);
	  const char &c1 = value.at(i1);
	  const char &c2 = value.at(neib_i);
	  if (offset > 0 && ((offset % 2 && !equal) || (!(offset % 2) && equal))) {
	    int pat = offset + 1;
	    res = (res * pat) % 1000000007;
	  }
	}
      }
      return res;
    }
};
