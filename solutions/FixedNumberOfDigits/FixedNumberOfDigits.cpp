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

 7/18/2020

 9:05-12:15 AC after contest ends
 12:42 add solution with simple code shown in the editorial.

 https://twitter.com/hanseilimak/status/1284576848064557056
 https://www.topcoder.com/2020-tco-round-2b-editorials/

 */

class FixedNumberOfDigits {
    public:
    int sz(LL a) {
        return SZ(to_string(a));
    }
    long long sum(LL s, LL d, LL tot) {
        LL cur=s;
        LL remd=tot;
        FOR(i,sz(s),18) {
            LL p10=1; REP(_,i) p10*=10;
            LL delta=(p10-cur+d-1)/d;
            if(i*delta<remd) {
                remd-=i*delta;
                cur+=d*delta;
                continue;
            }

            LL cnt=(remd+i-1)/i;
            cur+=d*(cnt-1);
            remd-=cnt*i;
            LL res=cur;
            while(remd<0) res/=10,remd++;
            return res;
        }
        assert(false);
    }
};

class FixedNumberOfDigits_org {
    public:
    LL s2ll(string s) {
        LL res=0;
        REP(i,SZ(s)) res=10LL*res+s[i]-'0';
        return res;
    }
    int sz(LL a) {
        return SZ(to_string(a));
    }
    long long sum(LL s, LL d, LL tot) {
        auto val=[&](LL step) {
            return s+d*step;
        };
        vector<LL> mxs(19);
        FORE(i,1,18) {
            LL good=1e18,bad=-1;
            while(abs(good-bad)>1) {
                LL m=(good+bad)/2;
                (sz(val(m))>=i?good:bad)=m;
            }
            //dump(i,good);
            mxs[i]=good;
        }

        int j=-1;
        LL dsum=0,remd=-1;
        FOR(i,sz(s),18) {
            assert(mxs[i]>=0);
            LL dsum2=dsum+(mxs[i+1]-mxs[i])*i;
            //dump(i,dsum2,tot);
            if(dsum2>=tot) {
                j=i,remd=tot-dsum;
                break;
            }
            dsum=dsum2;
        }
        assert(j>-1&&remd>0);
        LL cnt=(remd+j-1)/j,r=remd-(cnt-1)*j;
        LL base=val(mxs[j]), v=base+(cnt-1)*d;
        string ress=to_string(v).substr(0,r);

        return s2ll(ress);
    }
};

class FixedNumberOfDigits_wrong {
    public:
    long long sum(int start, int step, long long numberOfDigits) {
        numberOfDigits-=SZ(to_string(start));
        LL st=start+1,d=step;
        vector<LL> maxsteps(17,0);
        LL p10=1;
        REP(i,17) {
            maxsteps[i]=max(0LL,(p10-st+d-1)/d-1);
            dump(i,maxsteps[i]);
            p10*=10;
        }

        int d0=SZ(to_string(st));
        int j=0;
        LL remd=0,dcnt=0;
        REP(i,17) {
            if(i==d0) dcnt=d0;
            LL dsum=(maxsteps[i]-(i>0?maxsteps[i-1]:0))*i;
            dcnt+=dsum;
            dump(i,dsum,dcnt);
            if(dcnt<numberOfDigits) j=i,remd=numberOfDigits-dcnt;
        }

        LL a=(remd+j)/(j+1),b=remd-(a-1)*(j+1);
        LL base=st+d*(maxsteps[j]+a);
        string s=to_string(base);
        string res=s.substr(0,b);

        dump(j,remd,a,b,base,s,res);

        LL ans=0;
        REP(i,SZ(res)) ans=ans*10+res[i]-'0';
        return ans;
    }
};

// CUT begin
ifstream data("FixedNumberOfDigits.sample");

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

bool do_test(int start, int step, long long numberOfDigits, long long __expected) {
    time_t startClock = clock();
    FixedNumberOfDigits *instance = new FixedNumberOfDigits();
    long long __result = instance->sum(start, step, numberOfDigits);
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
        int start;
        from_stream(start);
        int step;
        from_stream(step);
        long long numberOfDigits;
        from_stream(numberOfDigits);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(start, step, numberOfDigits, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1595088332;
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
        cout << "FixedNumberOfDigits (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
