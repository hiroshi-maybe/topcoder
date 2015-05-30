#include <vector>
#include <string>
#include <cmath>
using namespace std;

int dis(int a[], int b[]) {
  return abs(a[0]-b[0]) + abs(a[1]-b[1]);
}

class PublicTransit {
public:
    int minimumLongestDistance(int R,
                               int C) {
      if (R < C) {
	int temp = R;
	R = C;
	C = temp;
      }
      
      int t1[2] = {C/2, 0};
      int t2[2] = {C/2, R-1};

      int s[2] = {0, 0};
      int e1[2] = {C-1, max(min((R+1)/2, R-1), 0)};
      int e2[2] = {C-1, max(min((R+1)/2-1, R-1), 0)};

      int far = min(dis(s, e1), dis(s, t1) + dis(t2, e1));
      int near = min(dis(s, e2), dis(s, t1) + dis(t2, e2));
      return max(near, far);
    }
};
