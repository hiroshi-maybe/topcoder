#include <fstream> // for greed plugin
#include <iostream>
#include <algorithm> // max,min
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <iostream>
#include <utility>
#include <cctype>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <limits.h>
#include <cstring>
#include <tuple>
#include <cassert>
#include <numeric>
#include <iomanip>
using namespace std;

// type alias
typedef long long LL;

typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<vector<int>> VVI;
typedef unordered_map<int,int> MAPII;
typedef unordered_set<int> SETI;
template<class T> using VV=vector<vector<T>>;

// minmax
template<class T> inline T SMIN(T& a, const T b) { return a=(a>b)?b:a; }
template<class T> inline T SMAX(T& a, const T b) { return a=(a<b)?b:a; }

// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// collection
#define ALL(c) (c).begin(),(c).end()

// pair/tuple
typedef pair<int,int> II;
typedef vector<II> VII;
typedef tuple<int,int,int> III;

// grid move (clock wise order)
vector<pair<int,int>> moves = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };
void move(int i, int j) {
  int N=0,M=0;
  // snippet of board move
  for(auto m : moves) {
    int ii=i+m.first,jj=j+m.second;
    if(ii<0||ii>=N||jj<0||jj>=M) continue;
  }
}
// knight walk
// http://gaebler.us/share/Knight_tour.html
vector<pair<int,int>> movesk = { {-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1} };
// grid moves with diagonal direction
vector<pair<int,int>> movesd = { {0,1}/*R*/,{1,1}/*RD*/,{1,0}/*D*/,{1,-1}/*DL*/,{0,-1}/*L*/,{-1,-1}/*UL*/,{-1,0}/*U*/,{-1,1}/*UR*/ };

// priority queue
#define MAX_PQ(T) priority_queue<T>
#define MIN_PQ(T) priority_queue<T,vector<T>,greater<T>>
#define PQ(T, comp, Q) priority_queue<T,vector<T>,decltype(&comp)> Q(&comp);

// dp
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))

// debug cerr
/*
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
 #define dumpf(args...) if(TRACE) { fprintf(stderr, ##args); putc('\n',stderr); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; } }
*/

// stdout
#define println(args...) fprintf(stdout, ##args),putchar('\n');

// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpf(args...) if(TRACE) { fprintf(stdout, ##args); putc('\n',stdout); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cout<<*begin<<','; } cout<<endl; } }

// main
#define MAIN int main(int argc, char const *argv[])

// mod
constexpr long long MOD = 1e9+7;

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG *.cpp && ./a.out

// standard io template
const int MAX_N=1e5+1;
int A[MAX_N];
int N;
int main(int argc, char const *argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  cin>>N;
  REP(i,N) cin>>A[i];
  
  int res=0;
  cout<<res<<endl;
  
  // more precision in double in iostream
  // cout<<setprecision(12)<<fixed<<res<<endl;
  
  return 0;
}

// highly composit number: http://wwwhomes.uni-bielefeld.de/achim/highly.txt
// math helper: http://www.wolframalpha.com/input/?i=sqrt(x*x+%2B+42)
// graph generator: http://emkjp.github.io/WebTools/dot.html
