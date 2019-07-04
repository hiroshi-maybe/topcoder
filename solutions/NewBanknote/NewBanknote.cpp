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
 
 7/4/2019
 
 13:32-13:55 WA
 15:23 give up. Read editorials
 16:36 got AC
 
 https://www.topcoder.com/blog/single-round-match-756-editorials/
 http://kmjp.hatenablog.jp/entry/2019/04/27/0900
 https://twitter.com/beet_aizu/status/1121392230785114117
 https://twitter.com/_olphe/status/1121392421714022401
 https://twitter.com/torus711/status/1121392953832828928
 https://twitter.com/n_vip/status/1121393074993688576
 https://twitter.com/n_vip/status/1121396619780321281
 https://twitter.com/satanic0258/status/1121393533733072896
 
 Obviously we can solve problem without new data by greedy.
 Try to reduce problem to the well-known problem.
 Do NOT mix new currency with original ones. It's making problem HARDER.
 It's just stupid 💩. Move to easier problem.

 From "How to solve it?"
 
 ```
 Find the connection between the data and the unknown. You may be obliged to consider auxiliary problems if an immediate connection cannot be found.
 
 Do you know a related problem? Do you know a theorem that could be useful? Look at the unknown! And try to think of a familiar problem having the same or a similar unknown. Here is a problem related to yours and solved before. Could you use it? Could you use its result? Could you use its method? Should you introduce some auxiliary element in order to make its use possible? Could you restate the problem? Could you restate it still differently?
 ```
 
 We should derive problem to a familiar problem which is clearly greedy.
 Thus we should solve a problem without new currency.
 How to do it? We just reduce amount contributed by new currency.
 How much we can reduce? Try all the number of new currency.
 What is maximum of it `cnt`?
 
 If C>50000, cnt<2*10^9/50000=4*10^4
 If C<50000, cnt<50000/3<=2*10^4
 
 Thus we can try cnt=0..4*10^4 times for either case.
 
 */

const int Inf=2e9;
vector<int> cs={1, 2, 5, 10, 20, 50, 100, 200,500, 1000, 2000, 5000, 10000, 20000, 50000 };
class NewBanknote {
  public:
  
  int f(int x) {
    int ans=0;
    FORR(c,cs) {
      ans+=x/c,x%=c;
    }
    return ans;
  }
  
  vector<int> fewestPieces(int C, vector<int> xs) {
    sort(ALL(cs)),reverse(ALL(cs));
    int N=SZ(xs);
    VI res(N);
    REP(i,N) {
      int x=xs[i];
      res[i]=Inf;
      REPE(cnt,4e4) if((LL)C*cnt<=(LL)x) {
        SMIN(res[i],cnt+f(x-C*cnt));
      }
    }
    return res;
  }
};

// CUT begin
ifstream data("NewBanknote.sample");

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

bool do_test(int newBanknote, vector<int> amountsToPay, vector<int> __expected) {
    time_t startClock = clock();
    NewBanknote *instance = new NewBanknote();
    vector<int> __result = instance->fewestPieces(newBanknote, amountsToPay);
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
        int newBanknote;
        from_stream(newBanknote);
        vector<int> amountsToPay;
        from_stream(amountsToPay);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(newBanknote, amountsToPay, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1562272331;
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
        cout << "NewBanknote (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
