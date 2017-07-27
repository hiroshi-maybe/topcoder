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
 
 7/26/2017
 
 8:37-8:45 (464.73 pt), missed condition N/2+1 :(
 8:45-9:45 give up
 13:48-14:00 passed system test
 
 23:56-24:20 read editorials
 - http://kmjp.hatenablog.jp/entry/2017/07/09/0930
  - very interesting technique
  - ignoring paired parentheses came up with me though, I ignored it because it seemed complex to map original index to chars after removal. However just replacing with irrelevant char resolves the issue!
 
 24:25-24:40 add solution with removal
 
 Same approach as my solution
 - https://community.topcoder.com/stat?c=problem_solution&rm=328554&rd=16709&pm=14225&cr=40037225
 - 
 
 Summary
 - tried to flip `()()()..` though, noticed that I was missing N/2+1 condition. It fails
 - tried to find existing pair and extend it though, it was not easy to keep extension
  - keep balance in left side and right side is not easy in this approach.
 - figured out that left most parenthesis must be '('. From that fact solved by keeping balance from left to right and flipping if needed.
 
 */
class ParenthesesDiv2Medium {
public:
  void test(string s, VI is) {
    FORR(i,is) {
      if(s[i]=='(') s[i]=')';
      else s[i]='(';
    }
    dump(s);
  }
  
  vector<int> correct(string s) {
    REP(j,SZ(s)) {
      for(int i=j-1; i>=0; --i) {
        if(s[i]=='('&&s[j]==')') {
          s[i]=s[j]='.';
          break;
        }
      }
    }
    
    VI res;
    int p=0;
    REP(i,SZ(s)) {
      if((p&1)&&s[i]=='(') {
        res.push_back(i);
      } else if((p&1)==0&&s[i]==')') {
        res.push_back(i);
      }
      if(s[i]!='.')++p;
    }
    
    return res;
  }
};

class ParenthesesDiv2Medium_org {
public:
  void test(string s, VI is) {
    FORR(i,is) {
      if(s[i]=='(') s[i]=')';
      else s[i]='(';
    }
    dump(s);
  }
  
  vector<int> correct(string s) {
    int bal = 0, N=SZ(s);
    VI res;
    REP(i,N) {
      if(bal==0 && s[i]==')') {
        res.push_back(i);
        ++bal;
      } else if(bal==N-i && s[i]=='(') {
        res.push_back(i);
        --bal;
      } else if(s[i]=='(') ++bal;
      else --bal;
    }
    assert(bal==0);
    assert(SZ(res)<=N/2+1);
    
    //test(s,res);
    
    return res;
  }
};

// CUT begin
ifstream data("ParenthesesDiv2Medium.sample");

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

bool do_test(string s, vector<int> __expected) {
    time_t startClock = clock();
    ParenthesesDiv2Medium *instance = new ParenthesesDiv2Medium();
    vector<int> __result = instance->correct(s);
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
        vector<int> __answer;
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
        int T = time(NULL) - 1501083422;
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
        cout << "ParenthesesDiv2Medium (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
