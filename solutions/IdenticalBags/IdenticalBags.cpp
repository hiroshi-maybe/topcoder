#include <bits/stdc++.h>
using namespace std;
// type alias
typedef long long LL;
typedef pair<int,int> II;
typedef tuple<int,int,int> III;
typedef vector<int> VI;
typedef vector<string> VS;
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
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// debug cerr
template<class Iter> void __kumaerrc(Iter begin, Iter end) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; }
void __kumaerr(istream_iterator<string> it) { (void)it; cerr<<endl; }
template<typename T, typename... Args> void __kumaerr(istream_iterator<string> it, T a, Args... args) {  cerr<<*it<<"="<<a<<", ",__kumaerr(++it, args...); }
template<typename S, typename T> std::ostream& operator<<(std::ostream& _os, const std::pair<S,T>& _p) { return _os<<"{"<<_p.first<<','<<_p.second<<"}"; }
#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

/*
 
 2/8/2019
 
 8:00-9:00 System test failed
 
 I found counter example of my solution by myself during the contest.
 
 Possible approaches
  - greedy
  - binary search
 
 `C` is large. I thought solution is either above.
 I couldn't find decision problem to binary search... 😞
 
 2/11/2019
 
 16:00-16:35 I retried by binary search and got AC by myself
 
 I had an idea of binary search. However I somehow thought that I need to make candy set whose summation is "exactly" `C`. However "at least" C is rigth condition. I was extraordinarily crazy during the contest.
 
 https://www.topcoder.com/blog/single-round-match-750-editorials/
 http://kmjp.hatenablog.jp/entry/2019/02/11/0900
 https://naoyat.hatenablog.jp/entry/SRM750
 
 */

bool ok(vector<LL> &A, LL C, LL k) {
  if(k==0) return true;
  LL cnt=0;
  FORR(a,A) {
    cnt+=a/k;
    if(cnt>=C) return true;
  }
  return cnt>=C;
}

LL f(vector<LL> A, LL C) {
  LL good=0,bad=(LL)1e18+1LL;
  while(abs(good-bad)>1) {
    LL m=(good+bad)/2;
    (ok(A,C,m)?good:bad)=m;
  }
  return good;
}

// 8:58 resubmit
LL f_wrong(vector<LL> A, LL C) {
  sort(A.rbegin(),A.rend());
  int N=SZ(A);
  LL res=0;
  FORE(l,1,N) {
    vector<LL> AA;
    REP(i,l) AA.push_back(A[i]/A[l-1]);
          dumpc(AA);
    bool more=false;
    LL sum=0;
    FORR(x,AA) {
      sum+=x;
      if(sum>C) {
        more=true;
        break;
      }
    }
    dump(sum);
    LL x=more?1:(C+sum-1)/sum;
    LL a=(LL)1e18+10;
    REP(i,l) {
      //        dump(i,A[i]/AA[i]/x);
      SMIN(a,A[i]/AA[i]/x);
    }
    //      dump(sum,x,a);
    SMAX(res,a);
  }
  return res;
}

class IdenticalBags {
  public:
  long long makeBags(vector<long long> A, long long C) {
    return f(A,C);
  }
};

// CUT begin
ifstream data("IdenticalBags.sample");

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

bool do_test(vector<long long> candy, long long bagSize, long long __expected) {
    time_t startClock = clock();
    IdenticalBags *instance = new IdenticalBags();
    long long __result = instance->makeBags(candy, bagSize);
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
        vector<long long> candy;
        from_stream(candy);
        long long bagSize;
        from_stream(bagSize);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(candy, bagSize, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1549641609;
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
        cout << "IdenticalBags (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
