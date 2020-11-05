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

 11/4/2020 SRM793

 18:05-19:20 give up

 21:30-22:42 read code by @nwin () and @hitonanode　(ternary search)

 https://twitter.com/hanseilimak/status/1324240490082885632

 */
class GoldMining {
    public:
    LL maxa,time,cost;
    LL f(LL cnt, bool dbg=false) {
        LL rem=maxa;
        if(dbg) dump(cnt);
        LL wf=1,cur=0;
        REP(t,time) {
            LL x=min(rem,wf);
            cur+=x,rem-=x;
            if(rem==0) return cur;
            if(cnt>0 && wf<cnt && cur>=cost) {
                LL newwf=min(cur/cost, cnt-wf);
                wf+=newwf;
                cur-=newwf*cost;
            }
            if(dbg) dump(t,wf,cur);
        }
        //if(wf<cnt) return 0;
        return min(cur,maxa);

/*
        LL rem=maxa,T=time,C=cost,nb=cnt;
        LL hito=1,ret=0;
        REP(t,T) {
            LL g=min(hito,rem);
            ret+=g,rem-=g;
            if(nb and ret>=C) {
                LL a=min(nb,ret/C);
                nb-=a,hito+=a;
                ret-=a*C;
            }
            if(dbg) dump(t,hito,ret,rem,nb);
        }
        return ret;*/
    }
    long long maxProfit(long long maxa, long long time, long long cost) {
        this->maxa=maxa,this->time=time,this->cost=cost;

        LL l=1,r=1e18;
        while(abs(l-r)>2) {
            LL ll=(l*2+r)/3,rr=(l+r*2)/3;
            LL vall=f(ll),valr=f(rr);
            if(vall>=valr) r=rr;
            else l=ll;
            //dump(l,r);
        }
        //dump(l,r);

        LL res=0;
        for(LL i=max(l-1,1LL); i<min(r+1,(LL)1e18); ++i) {
            //dump(i,f(i));
            SMAX(res,f(i));
        }
        //dump(f(12,true));
        return res;
    }
};

// CUT begin
ifstream data("GoldMining.sample");

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

bool do_test(long long goldInGround, long long miningTime, long long hiringCost, long long __expected) {
    time_t startClock = clock();
    GoldMining *instance = new GoldMining();
    long long __result = instance->maxProfit(goldInGround, miningTime, hiringCost);
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
        long long goldInGround;
        from_stream(goldInGround);
        long long miningTime;
        from_stream(miningTime);
        long long hiringCost;
        from_stream(hiringCost);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(goldInGround, miningTime, hiringCost, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1604541922;
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
        cout << "GoldMining (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
