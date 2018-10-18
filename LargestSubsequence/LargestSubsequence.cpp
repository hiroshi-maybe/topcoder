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
#define TRACE false
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 3/3/2018
 
 16:55-16:59 anslysis
 17:00-17:04 implement and ACC (456.26 pt)
 
 3/4/2018
 
 Read editorial and add greedy solution
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+518
   - recursive O(N^2) greedy solution
  - http://d.hatena.ne.jp/kusano_prog/20110914/1316010287
    - greedy by max_element()
  - http://purple-jwl.hatenablog.com/entry/20121106/1352206380
    - greedy by max_element()
  - https://chngng.blogspot.com/2013/10/srm-518-div1-easy-largestsubsequence.html
    - iterative O(N^2)
  - http://peryaudo.hatenablog.com/entry/20110917/1316267188
    - greedy linear solution
  - http://topcoder.g.hatena.ne.jp/firewood/20111018/1318953786

 I solved by dp quickly without going through greedy proof.
 However there is greedy solution.
 
 Lemma. it's always better to pick up largest character in left position.
 
 Suppose we have 'a' and 'z' and build subsequence with either one for leading character.
 In lexicographical order, 'z' > 'a'. Thus using larger one 'z' is always optimal.
 
 If we have two largest character 'z', using two 'z's is always lexicographically larger.
 Thus we can pick left one greedily.
 
 I added two linear runtime solutions based on above analysis
 
 1. T[i] keeps index of largest char in S[i..]
 
 As shown in the lemma, we want to put largest element in S[i..N-1].
 It's possible to remember the index of largest in single array `T`.
 
 T[i] = j s.t. S[j] is largest char in S[i..]
 
 We build this by iterating from tail to head because we need to know information of following elements.
 
 2. Create jump table `T`
 
 Let's assume each index of S has corresponding vertex of graph.
 If we create another vertex which represents initial state,
 we can build directed graph which forms DAG.
 If we want to solve "example"..
 
 012345678
  example$
 
 0->2->5->6->7->8 builds "xple", which is the solution that we want.
 We can build this graph by iterating from tail to head.
 If S[i-1] is largest, we can build edge (i-1)->i
 
 Summary:
  - I solved by dp quickly without going through greedy proof
  - I'm still bad at greedy linear solution 😞
   - I added two different solutions
   - O(N^2) solution is trivial. Optimizing O(N^2) solution by remembering something is key? 🤔
 
 10/17/2018
 
 solved with super simple algorithm
 
 */

class LargestSubsequence {
public:
  string getLargest(string S) {
    int N=SZ(S);
    string res;
    for(int i=N-1; i>=0; --i) {
      if(res.empty()) res+=S[i];
      else if(S[i]>=res[0]) res=string(1,S[i])+res;
    }
    return res;
  }
};

class LargestSubsequence_jumptable {
public:
  string getLargest(string S) {
    int N=SZ(S);
    // T[i] keeps index of largest char in S[i..]
    VI T(N+1);
    T[N]=N+1;
    for(int i=N; i>0; --i) {
      T[i-1]=T[i];
      if(S[i-1]>=S[T[i]-1]) T[i-1]=i;
    }
    dumpAR(T);
    string res="";
    int i=0;
    while(i<N) res+=S[T[i]-1],i=T[i];
    return res;
  }
};

// O(N) time, O(N) space
class LargestSubsequence_linear {
public:
  string getLargest(string S) {
    int N=SZ(S);
    // T[i] keeps index of largest char in S[i..]
    // e,x,a,m,p,l,e
    // 1,1,4,4,4,5,6
    VI T(N,N-1);
    int p=N-1;
    for(int i=N-2; i>=0; --i) {
      if(S[i]>=S[p]) T[i]=i,p=i;
      else T[i]=p;
    }
//    dumpAR(T);
    string res="";
    REP(i,N) if(T[i]==i) res+=S[i];
    return res;
  }
};

// O(N^2) time, O(1) space
class LargestSubsequence_greedy {
public:
  string getLargest(string S) {
    int N=SZ(S);
    
    string res="";
    int i=0;
    while(i<N) {
      i=max_element(S.begin()+i,S.end())-S.begin();
      res+=S[i++];
    }
    return res;
  }
};

// dp, O(N^3) time, O(N) space
string dp[51];
class LargestSubsequence_org {
  public:
  string getLargest(string S) {
    int N=SZ(S);
    REPE(i,N) dp[i]="";
    
    string res="";
    REP(j,N) {
      string s(1,S[j]);
      REP(i,j) {
        string t=dp[i]; t+=S[j];
        SMAX(s,t);
      }
      dp[j]=s;
      SMAX(res,s);
    }
    return res;
  }
};

// CUT begin
ifstream data("LargestSubsequence.sample");

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

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(string s, string __expected) {
    time_t startClock = clock();
    LargestSubsequence *instance = new LargestSubsequence();
    string __result = instance->getLargest(s);
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
        string s;
        from_stream(s);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1520124918;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "LargestSubsequence (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
