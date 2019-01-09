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

/*
 
 7/1/2017
 
 22:05-22:35 passed samples
 passed system tests
  
 read https://community.topcoder.com/stat?c=problem_solution&rd=16881&rm=329959&cr=23202843&pm=14567
 read https://www.topcoder.com/blog/single-round-match-712-editorialsl/
 
 add simpler solution
 
 */

// O(N) time, O(N) space
class MakePalindrome {
public:
  vector<string> constructMinimal(string card) {
    int cs[26]={0};
    FORR(c,card) ++cs[c-'a'];
    
    vector<string> res;
    REP(i,26) {
      if (cs[i]%2==0) continue;
      --cs[i];
      char c = 'a'+i;
      string x; x.push_back(c);
      res.push_back(x);
    }
    
    if (res.empty()) res.push_back("");
    string h;
    REP(i,26) {
      if (cs[i]==0) continue;
      char c = 'a'+i;
      h.append(cs[i]/2, c);
    }
    res[0] += h;
    reverse(res[0].begin(),res[0].end());
    res[0] += h;
    
    return res;
  }
};

class MakePalindrome_org {
  public:
  vector<string> constructMinimal(string card) {
    int cs[26]={0};
    FORR(c,card) ++cs[c-'a'];
    
    queue<int> OQ, EQ;
    REP(i,26) {
      if (cs[i]==0) continue;
      
      if (cs[i]%2==1) {
        OQ.push(i);
        --cs[i];
      }
      cs[i]/=2;
      while(cs[i]>0) {
        EQ.push(i);
        --cs[i];
      }
    }
    
    vector<string> res;
    while(EQ.size()&&OQ.size()) {
      int ei = EQ.front(); EQ.pop();
      int oi = OQ.front(); OQ.pop();
      
      char oc ='a'+oi, ec = 'a'+ei;
      string x = "";
      x.push_back(ec); x.push_back(oc); x.push_back(ec);
      res.push_back(x);
    }
    
    if (EQ.empty()) {
      while(OQ.size()) {
        int oi = OQ.front(); OQ.pop();
        char c ='a'+oi;
        string x; x.push_back(c);
        res.push_back(x);
      }
    }
    
    if (EQ.size()&&res.empty()) res.push_back("");
    string x = res.back();
    while (EQ.size()) {
      int ei = EQ.front(); EQ.pop();
      char ec = 'a'+ei;
      string y;
      y.push_back(ec); y+=x; y.push_back(ec);
      x = y;
    }
    res[SZ(res)-1] = x;
    return res;
  }
};

// CUT begin
ifstream data("MakePalindrome.sample");

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

bool do_test(string card, vector<string> __expected) {
    time_t startClock = clock();
    MakePalindrome *instance = new MakePalindrome();
    vector<string> __result = instance->constructMinimal(card);
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
        string card;
        from_stream(card);
        next_line();
        vector<string> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(card, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1498971896;
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
        cout << "MakePalindrome (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
