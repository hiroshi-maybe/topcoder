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
 
 2/4/2018
 
 17:51-18:26 pause
 22:40-23:18 submit and 1WA
 23:19-23:22 fixed ternary search bug and ACC
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+540
    - solve equations and inequations
  - https://apps.topcoder.com/forums/?module=Thread&threadID=743163&start=0
  - simple +1/-1 interval update
   - http://d.hatena.ne.jp/kusano_prog/20120411/1334156540
   - http://d.hatena.ne.jp/komiyam/20120411/1334155188
   - http://lepton.hatenablog.jp/?page=1334230879
   - http://rkx1209.hatenablog.com/entry/2012/11/01/205619
   - http://naoyat.hatenablog.jp/entry/2012/04/11/230223
  - solving equations naiively
   - http://mayokoex.hatenablog.com/entry/2016/04/09/000521
 
 Suppose a[i-1] = s[i-1]*a[0]+q[i-1] (s[i-1]∈{1,-1})
 
 a) O[i]='+'
  a[i]=-s[i-1]*a[0]+b[i]-q
 b) O[i]='-'
  a[i]= s[i-1]*a[0]+q[i-1]-b[i]
 
 a') s[i] is +: a[0]>-q[i]
 b') s[i] is -: a[0]<q[i]
 
 Compute lower bound and upper bound for i=0..N-1.
 
 Ternary search for integers:
  - http://codeforces.com/blog/entry/11497
  - http://codeforces.com/blog/entry/43440
  - https://apps.topcoder.com/forums/?module=Thread&threadID=670169&start=0
 
 Key:
  - If first element is fixed, other elements are determined
  - Length of a range of first element is the solution
  - By operation +/-, a0's range is determined
    - I didn't take this way
 
 Summary:
  - Tough problem
   - 34% successful submission in div1
   - Only 22 contestants solved in div2
  - It took long time to figure out one continuous interval is solution by playing around samples if exists
  - It took long time to find how to compute the interval (integer ternary search)
  - I eventually used ternary search and two binary searches
 
 */

// math, O(N) time
class ImportantSequence {
public:
  int getCount(vector<int> B, string O) {
    const LL Inf=1e11;
    LL l=0,r=Inf;
    int sign=1; LL q=0;
    REP(i,SZ(B)) {
      if(O[i]=='+') {
        sign^=1;
        q=B[i]-q;
      } else {
        q=q-B[i];
      }
      if(sign) l=max(l,-q);
      else r=min(r,q);
    }
    LL dif=r-1-l;
    if(dif<=0) return 0;
    if(r==Inf) return -1;
    return dif;
  }
};

// binary search, O(N*lg V) time
class ImportantSequence_binarysearch {
public:
  VI B;
  string O;
  LL sum(LL x) {
    LL sum=0,cnt=0;
    int N=SZ(B);
    REP(i,N) {
      LL y=0;
      if(O[i]=='+') {
        y=1LL*B[i]-x;
      } else {
        y=x-1LL*B[i];
      }
      if(y>0) ++cnt;
      else sum+=y;
      x=y;
    }
    return cnt==N?1:sum;
  }
  int getCount(vector<int> _B, string _O) {
    this->B=_B,this->O=_O;
    
    if(count(O.begin(),O.end(),'+')==0) return -1;
    
    LL good=0,bad=1e11;
    while(abs(good-bad)>1) {
      LL mid=(good+bad)/2;
      LL a=sum(mid-1),b=sum(mid);
      (a<b?good:bad)=mid;
    }
    if(good==0&&sum(good+1)<1) return 0;
    if(sum(good)<=0) return 0;
    LL l=max(1LL,good);
    
    good=1e11,bad=0;
    while(abs(good-bad)>1) {
      LL mid=(good+bad)/2;
      LL a=sum(mid),b=sum(mid+1);
      (a>b?good:bad)=mid;
    }
    LL r=good;
    dump2(l,r);
    //assert(l<=r);
    return max((int)(r-l+1),0);
  }
};

// ternary/binary search, O(N*lg V) time
class ImportantSequence_org {
  public:
  VI B;
  string O;
  LL sum(LL x) {
    LL sum=0,cnt=0;
    int N=SZ(B);
    REP(i,N) {
      LL y=0;
      if(O[i]=='+') {
        y=1LL*B[i]-x;
      } else {
        y=x-1LL*B[i];
      }
      if(y>0) ++cnt;
      else sum+=y;
      x=y;
    }
    return cnt==N?1:sum;
  }
  int getCount(vector<int> _B, string _O) {
    this->B=_B,this->O=_O;
    
    if(count(O.begin(),O.end(),'+')==0) return -1;
    
    LL l=0, r=1e11;
    while(abs(r-l)>2) {
      LL ll=l+(r-l)/3;
      LL rr=r-(r-l)/3;
      LL lv=sum(ll),rv=sum(rr);
      if(lv<rv) l=ll;
      else r=rr;
    }
    LL mid=-1;
    dump4(l,r,sum(l),sum(r));
    if(sum(l)==1) mid=l;
    else if(sum(l+1)==1) mid=l+1;
    else if(sum(r)==1) mid=r;
    else return 0;
    
    LL good=mid,bad=0;
    while(abs(good-bad)>1) {
      LL mid=(good+bad)/2;
      (sum(mid)==1?good:bad)=mid;
    }
    l=max(1LL,good);
    
    good=mid,bad=1e11;
    while(abs(good-bad)>1) {
      LL mid=(good+bad)/2;
      (sum(mid)==1?good:bad)=mid;
    }
    r=good;
    dump3(l,mid,r);
    //assert(l<=r);
    return max((int)(r-l+1),0);
  }
};

// CUT begin
ifstream data("ImportantSequence.sample");

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

bool do_test(vector<int> B, string operators, int __expected) {
    time_t startClock = clock();
    ImportantSequence *instance = new ImportantSequence();
    int __result = instance->getCount(B, operators);
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
        vector<int> B;
        from_stream(B);
        string operators;
        from_stream(operators);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(B, operators, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1517709070;
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
        cout << "ImportantSequence (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
