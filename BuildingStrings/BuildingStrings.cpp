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

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// debug cerr
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define dump2(x,y)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cerr << endl;

/**
 
 7/4/2017
 
 17:14-17:58 passed samples (227.75 pt)
 18:34 WA for 52
 18:36 passed
 
 read https://community.topcoder.com/stat?c=problem_solution&rm=329687&rd=16852&pm=14538&cr=40001774
 19:54 add simpler base-50 solution
 20:29 add solution by DP
 
 */

// https://community.topcoder.com/stat?c=problem_solution&rd=16852&rm=329690&cr=40529803&pm=14538
// DP solution
const int MX = 1305;
int chk[50005];
int tr[50005];
class BuildingStrings{
public:
  string P[MX];
  vector<string> findAny(int K){
    for(int i = 1; i <= 26; i++){
      for(int j = i; j <= 50; j++){
        if( P[i*j].size() ) continue;
        for(int k = 1; k <= i; k++) P[i*j] += k + 'a' - 1;
        for(int k = i+1; k <= j; k++) P[i*j] += 'a';
      }
    }
    chk[0] = 0;
    for(int i = 1; i <= K; i++) chk[i] = 1e9;
    for(int i = 1; i <= 1300; i++){
      if( P[i].size() == 0 ) continue;
      for(int j = i; j <= K; j++){
        // make an edge to j with `i` interval by DP table `chk`
        if( chk[j-i] + 1 >= chk[j] ) continue;
        // optimal path from j-i to j found
        chk[j] = chk[j-i] + 1; tr[j] = i;
      }
    }
    int c = K;
    vector<string> ans;
    // back track optimal path
    while(c){
      ans.push_back(P[tr[c]]);
      c -= tr[c];
    }
    return ans;
  }
};

string make(int len, int alpha) {
  string res="";
  REP(i,alpha) res.push_back('a'+i);
  REP(_,len-alpha) res.push_back('a');
  return res;
}

void test(vector<string> ss, int K) {
  int sum=0;
  FORR(s,ss) {
    assert(SZ(s)<=50);
    SETI S;
    FORR(c,s) S.insert(c-'a');
    sum+=SZ(S)*SZ(s);
  }
  dumpAR(ss);
  dump2(sum,K);
  assert(sum==K);
}

// https://community.topcoder.com/stat?c=problem_solution&rm=329687&rd=16852&pm=14538&cr=40001774
// base 50 solution
class BuildingStrings_base50 {
public:
  vector<string> findAny(int K) {
    int n=K/50, m=K%50;
    
    vector<string> res;
    while(n>=26) {
      res.push_back(make(50,26));
      n-=26;
    }
    if (n>0) res.push_back(make(50,n));
    if (m>0) res.push_back(make(m,1));
    
//    test(res,K);
    
    return res;
  }
};

// base 26 solution
class BuildingStrings_org {
  public:
  vector<string> findAny(int _K) {
    int K=_K;
    vector<string> res;
    int n1=K/1300;
    while(n1>0) {
      res.push_back("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwx");
      --n1;
    }
    K%=1300;
//    dump(K);
    int n2=K/26;
    if(n2>25) {
      string s="abcdefghijklmnopqrstuvwxyz";
      s.append(n2-26,'a');
      res.push_back(s);
      K-=n2*26;
    }
//    dump(K);
    int n3=K/26;
    if (n3>0) {
      string s; s.append(26-n3+1,'a');
      REP(i,n3-1) s.push_back('b'+i);
      res.push_back(s);
    }
    K%=26;
//    dump(K);
    string s; s.append(K,'a');
    if(SZ(s)) res.push_back(s);
    
//    test(res,_K);
    
    return res;
  }
};

// CUT begin
ifstream data("BuildingStrings.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(int K, vector<string> __expected) {
    time_t startClock = clock();
    BuildingStrings *instance = new BuildingStrings();
    vector<string> __result = instance->findAny(K);
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
        int K;
        from_stream(K);
        next_line();
        vector<string> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1499213643;
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
        cout << "BuildingStrings (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
