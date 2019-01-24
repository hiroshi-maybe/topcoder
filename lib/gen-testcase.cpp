#include <iostream>
#include <vector>
#include <utility>

using namespace std;

/*
 
 Generate sequence of pseudo-random numbers
 
 - fixed size
 - elements are in range [lb,ub)
 
 References:
  - https://codeforces.com/blog/entry/61587
   - why rand() is harmful?
  - https://codeforces.com/blog/entry/61675
   - hacking poor randomization in codeforces
 
 */
#include <chrono>
#include <random>
// mt19937_64 for 64 bit unsigned integer
//mt19937 rnd(time(nullptr));
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}
vector<int> genRandSeq(int size, int lb, int ub) {
  if (size==0) return {};
  vector<int> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}
// tested at https://github.com/hiroshi-maybe/leetcode/blob/master/384-Shuffle-an-Array/ShuffleArray.cpp
vector<int> shuffle(vector<int> &A) {
  int N = A.size();
  vector<int> res(N);
  for(int i=0; i<N; ++i) {
    // res[0..i-1] has org[0..i-1]
    res[i] = A[i];
    int r = rnd() % (i+1);
    swap(res[i],res[r]);
  }
  return res;
}

/*
 
 Usage:
 
 // GCD "size s[0], s[1], ..."
 $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG gen-testcase.cpp && ./a.out -s 100 -l 0 -l 10
 
 // TopCoder (greed plugin) "size↩︎s[0]↩︎s[1]↩︎ ..."
 $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG gen-testcase.cpp && ./a.out -s 100 -l 0 -l 10 -f tc
 
 */

// GCD:
// TopCoder (greed plugin): $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG gen-testcase.cpp && ./a.out -s 100 -l 0 -l 10 -f tc
int main(int argc, char const *argv[]) {
  if (argc < 7) {
    std::cerr << "Usage: " << argv[0] << " -s size -l lower_bound -u upper_bound -f tc" << std::endl;
    return 1;
  }
  
  int lb = 0, ub = 100, len = 100;
  string sep = " ";
  for (int i = 1; i < argc; i+=2) {
    if(i+1>=argc) break;
    string k=argv[i],v=argv[i+1];
    if(k.size()!=2||k[0]!='-') continue;

    char opt=k[1];
    switch (opt) {
    case 's':
      len = stoi(v);
      break;
    case 'l':
      lb = stoi(v);
      break;
    case 'u':
      ub = stoi(v);
      break;
    case 'f':
      sep = v=="tc"?"\n":" ";
      break;
    }
  }

  printf("** %d elements in [%d,%d)\n", len,lb,ub);
  
  vector<int> seq = genRandSeq(len, lb, ub);
  
  int N=seq.size();
  cout << N << sep;
  for(int i=0; i<N-1; ++i) cout << seq[i] << sep;
  if (N>1) cout << seq[N-1] << endl;
  else cout << endl;
  return 0;
}
