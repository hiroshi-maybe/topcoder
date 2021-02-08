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

 2/6/2021 SRM799

 10:05-11:16 failed system test
 11:56 fixed the solution and got AC

 https://docs.google.com/document/d/e/2PACX-1vTYud8UIgXGRaThfkjr4_rzdDDguw28kG6OizCi1gAHYRn8neDV2GJe1sU5wJQLORs1AliFe5G9dqV5/pub

 https://twitter.com/HIR180/status/1358138716473020420
 https://twitter.com/kzyKT_M/status/1358139359480848384
 https://twitter.com/natsugir/status/1358141408364818432?s=20

 */
string n2bin(long long n) {
  assert(n>=0);
  string res="";
  while(n>0) res+=(n%2LL?'1':'0'),n/=2LL;
  return string(9-SZ(res),'0') + string(res.rbegin(), res.rend());
}
bool ith(int mask, int i) { return (mask>>i)&1; }
class CapriciousSorting {
    public:
    int count(vector<int> A) {
        int N=SZ(A);
        /*
        dump("");
        REP(i,N) {
            dump(i,n2bin(A[i]),A[i]);
        }*/

        int res=1;
        VV<int> gs=VV<int>(1,A);
        for(int i=29; i>=0; --i) {
            bool same=true;
            VV<int> gs2;
            //dump(i);
            VI ord(2);
            FORR(g,gs) {
                //dumpc(g);
                VV<int> rl;
                REP(j,SZ(g)) {
                    //if(i==3||i==2)dump(i,j,g[j],ith(g[j],i));
                    if(j==0||(ith(g[j],i)!=ith(g[j-1],i))) rl.push_back({});
                    rl.back().push_back(g[j]);
                }
                //dump(i,SZ(rl));
                if(SZ(rl)>2) return 0;
                same&=(SZ(rl)==1);
                FORR(x,rl) gs2.push_back(x);
                if(SZ(rl)==2) ord[ith(rl[0].back(),i)<ith(rl[1].back(),i)]++;
            }
            //dump(i,SZ(gs),same);
            if(ord[0]>0&&ord[1]>0) return 0;
            if(same) res*=2;
            gs=gs2;
        }
        if(SZ(gs)!=N) return 0;
        return res;
    }
};

// CUT begin
ifstream data("CapriciousSorting.sample");

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

bool do_test(vector<int> num, int __expected) {
    time_t startClock = clock();
    CapriciousSorting *instance = new CapriciousSorting();
    int __result = instance->count(num);
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
        vector<int> num;
        from_stream(num);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(num, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1612634743;
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
        cout << "CapriciousSorting (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
