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

 9/10/2020

 8:55-9:20 give up

 9/13/2020

 14:45-16:45 Read editorials and @hitonanode's code

 https://kmjp.hatenablog.jp/entry/2020/09/13/0930
 https://docs.google.com/document/d/e/2PACX-1vQbYZAeAfdob4KjswmT14CZL0BhAJB8Q3c9O_OroMHzekTWplH6wJBcqPSuRFGa2nZIsjQgWWV9ENF9/pub
 https://twitter.com/kyort0n/status/1304097659150430208
 https://twitter.com/kinaba/status/1304099833507061760

 */
class ProposalOptimization {
    public:
    int N,M,K;
    VI R,T,C;
    vector<double> A;
    VV<pair<double,int>> B;

    bool ok2(int cur, int nxt) {
        int r=SZ(B[nxt])-1;
        int rem=K-C[nxt]-C[cur];
        double score=A[cur]+A[nxt];
        int minc=1.01e9;
        FORR(p, B[cur]) {
            while(r>=0&&p.first+B[nxt][r].first+score>=0) {
                SMIN(minc, B[nxt][r].second);
                --r;
            }
            if(minc+p.second<=rem) return true;
        }
        return false;
    }

    bool ok(double x) {
        A.resize(N*M);
        REP(i,N*M) A[i]=R[i]-x*T[i];
        B.assign(N*M,{});
        B[0].emplace_back(0,0);
        B.back().emplace_back(0,0);
        int mid = (N+M-1)/2;
        REP(i,N)REP(j,M) {
            if(i+j+1>mid) continue;
            int cur=i*M+j;
            FORR(p, B[cur]) {
                pair<double,int> nxt={p.first+A[cur], p.second+C[cur]};
                // right
                if(j+1<M) B[cur+1].emplace_back(nxt);
                // down
                if(i+1<N) B[cur+M].emplace_back(nxt);
            }
        }

        for(int i=N-1; i>=0; --i) for(int j=M-1; j>=0; --j) {
            if(i+j-1<=mid) continue;
            int cur=i*M+j;
            FORR(p, B[cur]) {
                pair<double,int> nxt={p.first+A[cur], p.second+C[cur]};
                // left
                if(j-1>=0) B[cur-1].emplace_back(nxt);
                if(i-1>=0) B[cur-M].emplace_back(nxt);
            }
        }

        REP(i,N)REP(j,M) {
            int cur=i*M+j;
            if(i+j==mid||i+j==mid+1) sort(ALL(B[cur]));
        }
        REP(i,N)REP(j,M) if(i+j==mid) {
            int cur=i*M+j;
            if(i+1<N&&ok2(cur,cur+M)) return true;
            if(j+1<M&&ok2(cur,cur+1)) return true;
        }
        return false;
    }

    double bestPath(int N, int M, int K, vector<int> R, vector<int> T, vector<int> C)
    {
        this->N=N,this->M=M,this->K=K,this->R=R,this->T=T,this->C=C;
        double good=0,bad=1.01e6;
        if(!ok(0)) return -1;
        REP(_, 60) {
            double m=(good+bad)/2;
            bool res=ok(m);
            (res?good:bad)=m;
        }
        return good;
    }
};

// CUT begin
ifstream data("ProposalOptimization.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(int R, int C, int K, vector<int> roses, vector<int> tulips, vector<int> costs, double __expected) {
    time_t startClock = clock();
    ProposalOptimization *instance = new ProposalOptimization();
    double __result = instance->bestPath(R, C, K, roses, tulips, costs);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
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
        int R;
        from_stream(R);
        int C;
        from_stream(C);
        int K;
        from_stream(K);
        vector<int> roses;
        from_stream(roses);
        vector<int> tulips;
        from_stream(tulips);
        vector<int> costs;
        from_stream(costs);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(R, C, K, roses, tulips, costs, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1599753124;
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
        cout << "ProposalOptimization (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
