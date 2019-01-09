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
typedef long long LL;
typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 9/7/2018
 
 16:42-17:17 give up
 17:51 I cannot prove
 
 20:50-21:50 Make rough proof of correctness of equal array rotation
 
 It's quite hard to figure out property of cycle if rotated string is equal.
 Experimentation would be needed to guess it.
 
 Suppose we have string "abcdef".
 If we rotate it at each index...
 
 1) i=1
 abcdef => bcdefa
           abcdef
 
 This is showing that a=b=c=d=e=f. Thus only "aaaaaa" can satisfy it.
 
 2) i=2
 abcdef => cdefab
           abcdef
 
 This is showing a=c=e, b=d=f. Thus only "ababab" can satisfy it.
 
 3) i=3
 abcdef => defabc
           abcdef
 
 a=d, b=e, c=f => "abcabc" can hold it.
 
 4) i=4
 abcdef => efabcd
           abcdef
 
 a=c=e, b=d=f => "ababab", this is same as i=2.
 
 From this experiment, sounds like if rotation at `i` is equal, cycle of size `i` needs to happen.
 
 If S(i) == S,
 
 S[0]=S[i],S[1]=S[i+1],..,S[i-1]=S[2*i-1],S[2*i]=S[i]=S[0],S[2*i+1]=S[i+1]=S[1],...,S[N-1]=S[i-1]
 
 Thus i|N. S[0..i-1]=S[i..2*i-1]=...=S[2*N-i..2*N-1]. Also S[0..i-1] should be smallest cycle.
 This is necessary and sufficient condition of K magic word.
 
 Once this property is found, just check it.
 Checking equality of S[0..K-1] for S[p*K..(p+1)*K-1] is linear time check.
 
 Check of cycle of S[0..K-1] is feasible in O(sqrt(K)*K) by trial division.
 
 21:50-22:41 add solution
 
 https://www.topcoder.com/tc?module=Static&d1=match_editorials&d2=srm433
 http://d.hatena.ne.jp/simezi_tan/20111214/1323852898
 http://rsujskf.blog32.fc2.com/blog-entry-195.html
 https://chngng.blogspot.com/2015/05/srm-433-div1-easy-magicwords.html
 https://qnighy.hatenablog.com/entry/20090121/1232560514
 
 Summary:
  - I messed up to prove general properties of general rotation. I should have tried short example like "abcdef" or "123456"
 
 */

bool cycle(string s, int L) {
  int M=SZ(s);
  bool ok=true;
  REP(p,M/L) ok&=s.substr(p*L,L)==s.substr(0,L);
  return ok;
}

class MagicWords {
  public:
  int count(vector<string> S, int K) {
    int N=SZ(S),M=0; REP(i,N)M+=SZ(S[i]);
    VI P(N); REP(i,N)P[i]=i;
    int res=0;

    VI divs;
    if(M!=K) divs.push_back(1);
    int L=M/K;
    for(int p=2; p*p<=L; ++p) if(L%p==0) {
      divs.push_back(p);
      if(p!=L/p) divs.push_back(L/p);
    }
//    dumpAR(divs);
    
    do {
      string s;
      REP(i,N) s+=S[P[i]];
      if(M%K!=0) return 0;
      
//      dump2(s,cycle(s,M/K));
      
      if(!cycle(s,M/K)) continue;
      
      bool cy=false;
      FORR(d,divs) {
        cy|=cycle(s.substr(0,M/K),d);
      }
      if(cy) continue;
//      dump(s);
      ++res;
    } while(next_permutation(P.begin(),P.end()));
    return res;
  }
};

// CUT begin
ifstream data("MagicWords.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(vector<string> S, int K, int __expected) {
    time_t startClock = clock();
    MagicWords *instance = new MagicWords();
    int __result = instance->count(S, K);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        vector<string> S;
        from_stream(S);
        int K;
        from_stream(K);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(S, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1536363736;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "MagicWords (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
