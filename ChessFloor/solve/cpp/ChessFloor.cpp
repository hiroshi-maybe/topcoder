#include <vector>
#include <string>
#include <map>
#include <math.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

bool myfunction (pair<char, int> i,pair<char, int> j) { return (i.second < j.second); }

class ChessFloor {
public:
    int minimumChanges(vector<string> const &floor) {
      map<char, int> charA;
      map<char, int> charB;
      REP(i,floor.size()) {
	REP(j,floor[i].size()) {
	  char curChar = floor[i][j];
	  if ((!(i % 2) && !(j % 2)) || ((i % 2) && (j % 2))) {
	    if (charA.find(curChar) == charA.end()) {
	      charA[curChar] = 0;
	    }
	    charA[curChar]++;
	  } else {
	    if (charB.find(curChar) == charB.end()) {
	      charB[curChar] = 0;
	    }
	    charB[curChar]++;
	  }
	}
      }

      vector<pair<char, int> > pairsA(charA.begin(), charA.end());
      vector<pair<char, int> > pairsB(charB.begin(), charB.end());
      sort(pairsA.begin(), pairsA.end(), myfunction);
      sort(pairsB.begin(), pairsB.end(), myfunction);

      int floorCount = floor.size()*floor.size();
      int countA = std::ceil(floorCount/2.0);
      int countB = std::floor(floorCount/2.0);

      auto maxA1 = pairsA[pairsA.size()-1];
      auto maxA2 = pairsA.size() > 1 ? pairsA[pairsA.size()-2] : make_pair('x', 0);
      
      auto maxB1 = pairsB[pairsB.size()-1];
      auto maxB2 = pairsB.size() > 1 ? pairsB[pairsB.size()-2] : make_pair('x', 0);

      if (maxA1.first != maxB1.first) {
	return countA - maxA1.second + countB - maxB1.second;
      }
      if ((countA - maxA1.second) > (countB - maxB1.second)) {
	return countA - maxA2.second + countB - maxB1.second;
      } else {
	return countA - maxA1.second + countB - maxB2.second;
      }
    }
};
