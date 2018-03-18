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
using namespace std;

// type alias
const int Inf = 1e9;
typedef long long LL;

typedef vector < bool > VB;
typedef vector < int > VI;
typedef vector < string > VS;
typedef vector < vector < int > > VVI;
typedef unordered_map < int, int > MAPII;
typedef unordered_map < string, int > MAPSI;
typedef unordered_set < int > SETI;
typedef unordered_set < string > SETS;

// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// vector
#define REVERSE(c) reverse((c).begin(),(c).end())
#define SORT(c) sort((c).begin(),(c).end())
#define CONCAT(a,b) (a).insert((a).begin(), (b).begin(),(b).end())

// pair/tuple
typedef pair< int , int > II;
typedef vector<II> VII;
typedef tuple< int, int, int > III;

// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)

// grid move (clock wise order)
vector< pair < int, int > >  moves = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };
// grid moves with diagonal direction
vector< pair < int, int > >  movesd = { {0,1}/*R*/,{1,1}/*RD*/,{1,0}/*D*/,{1,-1}/*DL*/,{0,-1}/*L*/,{-1,-1}/*UL*/,{-1,0}/*U*/,{-1,1}/*UR*/ };

// priority queue
#define MAX_PQ(T) priority_queue<T>
#define MIN_PQ(T) priority_queue<T,vector<T>,greater<T>>
#define PQ(T, comp, Q) priority_queue<T,vector<T>,decltype(&comp)> Q(&comp);

// binary search
#define LB(a,n,k) lower_bound(a,a+(n),(k))
#define UB(a,n,k) upper_bound(a,a+(n),(k))

// dp
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))

// debug cerr
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

// debug cout
//#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

// main
#define MAIN int main(int argc, char const *argv[])

// mod
constexpr long long MOD = 1e9+7;

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG *.cpp && ./a.out

// highly composit number: http://wwwhomes.uni-bielefeld.de/achim/highly.txt
// math helper: http://www.wolframalpha.com/input/?i=sqrt(x*x+%2B+42)
// graph generator: http://emkjp.github.io/WebTools/dot.html
