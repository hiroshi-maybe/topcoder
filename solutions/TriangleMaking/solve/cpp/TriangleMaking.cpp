#include <vector>
#include <string>
using namespace std;

#define SORT(c) sort((c).begin(),(c).end())

class TriangleMaking {
public:
  int maxPerimeter(int a,
                   int b,
                   int c) {
    vector<int> ns = {a, b, c};
    SORT(ns);
    
    while (ns[2] >= ns[0]+ns[1]) {
      ns[2]-=1;
    }

    return ns[0]+ns[1]+ns[2];
  }
};
