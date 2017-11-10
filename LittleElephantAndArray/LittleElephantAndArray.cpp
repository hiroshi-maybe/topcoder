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
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))

// debug cout
#define dump(x)  cout << #x << " = " << (x) << endl;
#define dump2(x,y)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cout << endl;

/*
 
 11/9/2017
 
 8:45-9:10 analysis
 9:11-10:08 implement and system test passed (352.38 pt)
 
 Number has at most 16 digits. There are at most 2^16-1 (≈7*10^4) ways to drop digits in S[i].
 Since |S|<=100, we need 100*2^16 ≈7*10^6 steps to enumerate all the patterns to drop digits.
 If we can count number of ways to select each number where digits are dropped in less than 100 step,
 we can compute expected number in time limit.
 If we build cumulative sum and do binary search at each S[i], total time is 100*2^16*log2(2^16)≈10^8
 We checkmated.
 
 Editorial:
  - https://apps.topcoder.com/wiki/display/tc/SRM+592
   - two pointers instead of binary search
  - http://kmjp.hatenablog.jp/entry/2013/09/29/0930
   - binary search
  - http://emkcsharp.hatenablog.com/entry/SRM592/LittleElephantAndArray
   - two pointers
  - http://topcoder.g.hatena.ne.jp/agw/20131003/1380788454
 
 Key:
  - bitmask to enumerate all the numbers in which digits are dropped
  - DP where state key is not consecutive
 
 Summary:
  - Solved by myself 👍
  - Analysis went well, implementation needs more improvement
  - I implemented bit mask in too complicated way first
 
 Only code which passed system tests during the contest:
  - https://community.topcoder.com/stat?c=problem_solution&rm=318901&rd=15704&pm=12704&cr=23080625
   - clean implementation
 
 */
constexpr int MOD = 1e9+7;
class LittleElephantAndArray {
public:
  int getNumber(long long A, int N) {
    vector<LL> ns(N+1,0);
    REP(i,N+1) ns[i]=A+i;
    
    vector<LL> ns1={-1};
    vector<LL> cnt1={0,1};
    REP(i,N+1) {
      string S=to_string(A+i);
      int L=SZ(S);
      vector<LL> ns2;
      REP(mask,1<<L) if(mask) {
        LL n=0;
        REP(i,L) if((mask>>i)&1) n=10*n+S[i]-'0';
        ns2.push_back(n);
      }
      int N1=SZ(ns1),N2=SZ(ns2);
      sort(ns2.begin(),ns2.end());
      vector<LL> cnt2(N2+1,0);
      int s=0;
      REP(t,N2) {
        if(ns1[0]>ns2[t]) continue;
        while(s<N1&&ns1[s]<=ns2[t]) ++s;
        // invariant: s==N1 or ns1[s-1]<=ns2[t]<ns1[s]
        cnt2[t+1]=cnt1[s];
        cnt2[t+1]+=cnt2[t], cnt2[t+1]%=MOD;
      }
//      dumpAR(ns2);
//      dumpAR(cnt2);
      swap(ns1,ns2);
      swap(cnt1,cnt2);
    }
    return cnt1.back();
  }
  
  // cumulative sum following official editorial
  int getNumber2(long long A, int N) {
    vector<LL> ns(N+1,0);
    REP(i,N+1) ns[i]=A+i;
    
    vector<LL> ns1={-1};
    vector<LL> cnt1={1};
    REP(i,N+1) {
      string s=to_string(A+i);
      int L=SZ(s);
      vector<LL> ns2;
      REP(mask,1<<L) if(mask) {
        LL n=0;
        REP(i,L) if((mask>>i)&1) n=10*n+s[i]-'0';
        ns2.push_back(n);
      }
      sort(ns2.begin(),ns2.end());
      vector<LL> cnt2(SZ(ns2),0);
      int j=0;
      REP(i,SZ(ns2)) {
        if(ns1[0]>ns2[i]) continue;
        while(j<SZ(ns1)-1&&ns1[j+1]<=ns2[i]) ++j;
//        dump4(i,j,ns1[j],ns2[i]);
//        dump(cnt1[j]);
        if(ns1[j]<=ns2[i]) cnt2[i]=cnt1[j];
        if(i>0) cnt2[i]+=cnt2[i-1], cnt2[i]%=MOD;
      }
//      dumpAR(ns2);
//      dumpAR(cnt2);
      swap(ns1,ns2);
      swap(cnt1,cnt2);
    }
    return cnt1.back();
  }
};

LL _pow10[18];
class LittleElephantAndArray_org {
  public:
  vector<int> digits(LL n) {
    VI res;
    while(n>0) {
      res.push_back(n%10);
      n/=10;
    }
    return res;
  }
  /*
  vector<LL> make(LL N) {
    vector<LL> res;
    VI ds=digits(N);
    int L=SZ(ds);
    dumpAR(ds);
    REP(i,L) {
      dump(i);
      REP(mask,1<<(L-1)) {
        int lmask=(1<<i)-1;
        int mask1=mask&lmask;
        int mask2=1<<i;
        int mask3=(mask-mask1)<<1;
        int mmask=mask1|mask2|mask3;
        assert(mmask<(1<<L));
        dump(mask);
        LL n=0;
        REP(i,L) if(mmask&(1<<i)) {
          n+=pow10[i]*ds[i];
        }
        res.push_back(n);
      }
    }
    return res;
  }*/
  vector<LL> make(LL N) {
    vector<LL> res;
    VI ds=digits(N);
    int L=SZ(ds);
//    dumpAR(ds);
    FOR(mask,1,1<<L) {
      LL n=0;
      int b=0;
      REP(i,L) if(mask&(1<<i)) {
        n+=_pow10[b++]*ds[i];
      }
      res.push_back(n);
    }
    return res;
  }
  map<LL,LL> makecum(vector<LL> &ns, map<LL,LL> &prev) {
    sort(ns.begin(),ns.end());
//    dumpAR(ns);
    int N=SZ(ns);
    vector<LL> cum(N+1,0);
    REP(i,N) {
      auto it=prev.upper_bound(ns[i]);
      LL cnt=1;
      if(it==prev.end()&&SZ(prev)==0) {
        cnt=1;
      } else if(it==prev.begin()) {
        cnt=0;
      } else {
        --it;
        cnt=it->second;
      }
      cum[i+1]=cum[i]+cnt,cum[i+1]%=MOD;
    }
    map<LL,LL> res;
    REP(i,N) res[ns[i]]=cum[i+1];
//    FORR(kvp,res) dump2(kvp.first,kvp.second);
    return res;
  }
  int getNumber(long long A, int N) {
    vector<LL> ns(N+1,0);
    REP(i,N+1) ns[i]=A+i;
    _pow10[0]=1LL;
    REP(i,17) _pow10[i+1]=10*_pow10[i];

    vector<LL> ms0=make(ns[0]);
    map<LL,LL> _={};
    map<LL,LL> cur=makecum(ms0,_);
    FOR(d,1,N+1) {
      vector<LL> xs=make(ns[d]);
      map<LL,LL> next=makecum(xs,cur);
      swap(cur,next);
    }
    
    return (*cur.rbegin()).second;
  }
};

// CUT begin
ifstream data("LittleElephantAndArray.sample");

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

bool do_test(long long A, int N, int __expected) {
    time_t startClock = clock();
    LittleElephantAndArray *instance = new LittleElephantAndArray();
    int __result = instance->getNumber(A, N);
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
        long long A;
        from_stream(A);
        int N;
        from_stream(N);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, N, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1510245909;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "LittleElephantAndArray (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
