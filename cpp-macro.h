#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

// container util
#define SZ(a) int((a).size())
#define EXIST(s,e) ((s).find(e)!=(s).end())
#define SORT(c) sort((c).begin(),(c).end())

// debug
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dumpAR(ar,n) REP(i,(n)) { cerr << ar[i] << ','; } cerr << endl;
