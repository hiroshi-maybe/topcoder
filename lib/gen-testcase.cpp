#include <iostream>
#include <vector>
#include <utility>

using namespace std;

/*
 
 Generate sequence of pseudo-random numbers
 
 - fixed size
 - elements are in range [lb,ub)
 
 */
int genRandNum(int lb, int ub) {
  // Helper to generate random integer in range [lb, ub)
  int x = rand() % (int)(ub - lb + 1.0);
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
