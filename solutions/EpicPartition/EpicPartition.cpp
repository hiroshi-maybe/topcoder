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
 
 3/19/2020
 
 18:00-19:15 give up
 
 3/21/2020
 
 15:30-16:27 read editorials and got AC
  
 https://www.topcoder.com/single-round-match-781-editorials/
 http://kmjp.hatenablog.jp/entry/2020/03/20/0900
 https://twitter.com/kmjp_pc/status/1240830856547069952
 https://twitter.com/natsugir/status/1240831036101029894
 
 */
class EpicPartition {
  public:
  string solve(int N) {
    if(N%4!=0) return "";
    
    string res(6*N,'c');
    string x="abba";
    REP(i,N)REP(j,4)res[4*i+j]=x[j];
    
    queue<int> Q; Q.emplace(4*N);
    int cnt=N*(2*N-1)/4;
    while(cnt>0) {
      assert(SZ(Q));
      int i=Q.front(); Q.pop();
      assert(res[i]=='c');
      if(i<2) continue;
      if(res[i-2]=='a'&&res[i-1]=='b') {
        res[i-2]='c',res[i-1]='a',res[i]='b';
        --cnt;
        Q.emplace(i-2);
        if(i+1<SZ(res)&&res[i+1]=='c') Q.emplace(i+1);
        continue;
      }
      if(res[i-2]=='b'&&res[i-1]=='a') {
        res[i-2]='c',res[i-1]='b',res[i]='a';
        --cnt;
        Q.emplace(i-2);
        if(i+1<SZ(res)&&res[i+1]=='c') Q.emplace(i+1);
        continue;
      }
    }
    
    VI sums(3),cnts(3);
    REP(i,SZ(res)) sums[res[i]-'a']+=i+1,cnts[res[i]-'a']++;
    assert(sums[0]==sums[1]&&sums[2]==sums[0]*2);
    assert(cnts[0]==cnts[1]&&cnts[0]==cnts[2]);

    return res;
  }
  
  vector<string> res;
  
  int N;
  void dfs(int i, VI &cnts, VI &sums, string &cur) {
    int tot=3*N*(6*N+1);
    if(cnts[0]>2*N) return;
    if(cnts[1]>2*N) return;
    if(cnts[2]>2*N) return;
    if(sums[0]>tot/4) return;
    if(sums[1]>tot/4) return;
    if(sums[2]>tot/2) return;

    if(i==6*N) {
//
      if(cnts[0]==2*N&&cnts[1]==2*N&&cnts[2]==2*N&&sums[0]==tot/4&&sums[1]==tot/4&&sums[2]==tot/2) {
        dumpc(cur);
        res.push_back(cur);
      }
      return;
    }
    
    REP(c,3) {
      cur[i]='a'+c;
      cnts[c]++,sums[c]+=i+1;
      dfs(i+1, cnts, sums, cur);
      cnts[c]--,sums[c]-=i+1;
    }
  }
  
  string createPartition(int N) {
    /*
    this->N=N;
    VI cnts(3),sums(3); string cur(6*N,'?');
    dfs(0,cnts,sums,cur);
    dump(SZ(res));*/
    return solve(N);
//    return solve(N);
  }
};

// CUT begin
ifstream data("EpicPartition.sample");

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

bool do_test(int N, string __expected) {
    time_t startClock = clock();
    EpicPartition *instance = new EpicPartition();
    string __result = instance->createPartition(N);
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
        int N;
        from_stream(N);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1584666155;
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
        cout << "EpicPartition (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
