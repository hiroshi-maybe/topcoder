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

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}
vector<int> genRandSeq(int size, int lb, int ub) {
  if (size==0) return {};
  vector<int> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}

/*
 
 6/4/2019 TCO 2019 R2B
 
 8:00-9:02 AC
 
 */
class MedianFaking {
  public:
  
  VI solve(int F, int M, vector<int> A, int G) {
    int N=F*M;
    int mp=(N-1)/2;
    VV<int> B(F,VI(M));
    REP(i,F)REP(j,M) B[i][j]=A[i*M+j];
    sort(ALL(A));
    //    dumpc(A);
    int ma=A[mp];
    if(ma==G) return VI({0,0});
    int delta=0;
    if(ma<G) {
      FOR(i,mp,N) if(A[i]<G) {
        ++delta;
      }
    } else if(ma>G) {
      for(int i=mp; i>=0; --i) if(A[i]>G)++delta;
    }
    //    dump(mp,ma,G,delta);
    vector<II> cnt(F);
    REP(i,F) {
      int x=0;
      REP(j,M) {
        if(ma<G) x+=B[i][j]<G;
        else x+=B[i][j]>G;
      }
      cnt[i]={x,i};
    }
    sort(ALL(cnt)),reverse(ALL(cnt));
    //        dumpc(cnt);
    int d=delta;
    int x=0;
    REP(i,F) if(d>0) {
      int a=min(d,cnt[i].first);
      d-=a;
      if(d==0) x=i+1;
    }
    
    // check
    {
      int d=delta;
      REP(i,F) if(d>0) {
        int a=min(d,cnt[i].first);
        int j=cnt[i].second;
        int aa=a;
        REP(k,M) if(aa>0) {
          if(ma<G&&B[j][k]<G) B[j][k]=G,--aa;
          else if(ma>G&&B[j][k]>G) B[j][k]=G,--aa;
        }
        d-=a;
        if(d==0) x=i+1;
      }
      VI C;
      REP(i,F)REP(j,M) C.push_back(B[i][j]);
      sort(ALL(C));
      assert(C[mp]==G);
    }
//    dump(x,delta);
    return {x,delta};
  }
  
  void test() {
    int F=genRandNum(1,10),M=genRandNum(1,10),G=genRandNum(0,100);
    VI A=genRandSeq(F*M,0,100);
    solve(F,M,A,G);
  }
  
  vector<int> minimize(int F, int M, vector<int> A, int G) {
    
    while(true) test();
    
    return solve(F,M,A,G);
  }
};

// CUT begin
ifstream data("MedianFaking.sample");

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

bool do_test(int F, int M, vector<int> data, int goal, vector<int> __expected) {
    time_t startClock = clock();
    MedianFaking *instance = new MedianFaking();
    vector<int> __result = instance->minimize(F, M, data, goal);
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
        int F;
        from_stream(F);
        int M;
        from_stream(M);
        vector<int> data;
        from_stream(data);
        int goal;
        from_stream(goal);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(F, M, data, goal, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1559660404;
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
        cout << "MedianFaking (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
