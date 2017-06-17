#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

#define dump(x)  cout << #x << " = " << (x) << endl;
#define dump2(x,y)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cout << endl;

bool lte(int n, int k) {
  return n<=k;
}

// max: [ok,ng), min: (ng,ok]
// move ok as long as `c` holds
int meguru(vector<int> ns, int ok, int ng, int k) {
  
  while(abs(ok-ng)>1) {
    int mid = (ng+ok)/2;
    bool c = ok<ng ? ns[mid]<=k : ns[mid]>=k;
    if (c) {
      ok = mid;
    } else {
      ng = mid;
    }
  }

  return ok;
}

void test(vector<int> ns, int k) {
  int N = ns.size();

  cout << "###################" << endl;
  cout << "test:" << k << endl;
  cout << "["<<0<<","<<N<<"):"; // max index which satisfies ns[u]>=k
  int u = meguru(ns, 0, N, k);
  cout << u << endl;

  int l = meguru(ns, N-1, -1, k);
  cout << "("<<-1<<","<<N-1<<"]:"; // min index which satisfies ns[l]<=k
  cout << l << endl;

  cout << "upper_bound():" << distance(ns.begin(), upper_bound(ns.begin(), ns.end(), k)) << endl; // upper bound = 7
  cout << "lower_bound():" << distance(ns.begin(), lower_bound(ns.begin(), ns.end(), k)) << endl; // lower bound = 3
}

int main(int argc, char const *argv[]) {
  // ns[3..6] = 3
  vector<int> ns = {1,2,2,3,3,3,3,5,7,7};
  for(auto &n: ns) cout << n << ",";
  cout << endl;

  test(ns,3);
  test(ns,0);
  test(ns,7);
  test(ns,8);
}
