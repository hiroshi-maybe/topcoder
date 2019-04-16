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
 
 4/11/2019
 
 16:38-17:20 give up
 20:30-22:56 read editorial and got AC
 
 http://kmjp.hatenablog.jp/entry/2019/03/22/0930
 https://www.topcoder.com/blog/single-round-match-753-editorials/
 
 Keys:
  - X[n+1]=(A*X[n]+C) % MOD is pseudorandom generator
  - Pair of maximum bitwise operation => Binary trie tree
 
 */

class TrieNode {
public:
  const char C_SIZE=2;
  const char BASE='0';
  int cnt=0; // # of strs in subtree
  set<int> ids; // str ending here
  vector<TrieNode*> cs;
  TrieNode() { this->cs=vector<TrieNode*>(C_SIZE,nullptr); }
  void release() { for(auto c : cs) if(c!=nullptr) c->release(), delete c; }
  void insert(int id, string &s, int p=0) {
    ++cnt;
    if(p==s.size()) {
      ids.emplace(id);
      return;
    }
    int i=index(s[p]);
    auto x=cs[i];
    if(x==nullptr) x=new TrieNode(),cs[i]=x;
    x->insert(id,s,p+1);
  }
  // true: erase success, false: failure, id:-1=>wildcard
  bool erase(int id, string &s, int p=0) {
    if(p==s.size()) {
      bool res=false;
      if(ids.count(id)) ids.erase(id),res=true;
      else if(id==-1) { // wildcard
        if(ids.size()) res=true,ids.erase(ids.begin());
        return res;
      }
      return res;
    }
    int i=index(s[p]);
    auto x=cs[i];
    if(x==nullptr) return false;
    bool res=x->erase(id,s,p+1);
    if(res) --cnt;
    return res;
  }
  TrieNode* find(string &s, int p=0) {
    if(p==s.size()) return this;
    int i=index(s[p]);
    if(cs[i]==nullptr) return nullptr;
    return cs[i]->find(s,p+1);
  }
  // success: id, failure: -1
  int search(string s) {
    TrieNode* n=find(s);
    return (n!=nullptr&&n->ids.size())?*(n->ids.begin()):-1;
  }
  // # of strs with prefix `p`
  int prefix(string p) {
    TrieNode* n=find(p);
    return n!=nullptr?n->cnt:0;
  }
  
  // id, value
  pair<int,LL> xorcp(string s, int p=0, LL val=0LL) {
    if(p==s.size()) {
//      assert(SZ(ids));
      return {*(ids.begin()), val};
    }
    int b=s[p]-'0';
    auto next=cs[b^1];
    if(next==nullptr||next->cnt==0) next=cs[b],val=val*2LL+b;
    else val=val*2LL+(b^1);
    assert(next!=nullptr);
    return next->xorcp(s,p+1,val);
  }
private:
  int index(char c) {
    int i=c-BASE;
    assert(0<=i&&i<C_SIZE);
    return i;
  }
};

const int MAX_D=31;
string tobin(LL x) {
  string res(MAX_D,'?');
  REP(i,MAX_D) res[i]='0'+((x>>i)&1);
  reverse(ALL(res));
//  dump(x,res);
  return res;
}

const LL MOD=1e9+7;
class MojisBag {
  public:
  int maximumXor(int Q, int B, int A, int R) {
    TrieNode* trie=new TrieNode();
    II maxp={-1,-1};
    LL x=A;
    set<int> valid;
    vector<LL> S,Y,Z;
    auto add=[&](LL x, int id) {
      string xs=tobin(x);
      if(maxp.first!=-1||maxp.second!=-1) {
        auto p=trie->xorcp(xs);
        if(maxp.first==-1||maxp.second==-1) {
          maxp={id,p.first};
        } else if((x^p.second)>(S[maxp.first]^S[maxp.second])) {
          maxp={id,p.first};
        }
      } else maxp={id,-1};
      
      trie->insert(id,xs);
      valid.emplace(id);
    };
    REP(i,Q) {
//      dump(i,x,x%R);
      if(x%R!=0) {
        // add
        add(x,SZ(S));
        S.push_back(x);
      } else if(SZ(S)) {
        // erase
        int remid=x%SZ(S);
        if(valid.count(remid)) {
          valid.erase(remid);
          string s=tobin(S[remid]);
          trie->erase(remid,s);
          if(remid==maxp.first||remid==maxp.second) {
            maxp={-1,-1};
            FORR(i,valid) {
              string s=tobin(S[i]);
              trie->erase(i,s);
            }
            FORR(i,valid) add(S[i],i);
          }
        }
      }
//      dump(i,maxp.first,maxp.second);
      LL y=(maxp.first==-1||maxp.second==-1)?0:S[maxp.first]^S[maxp.second];
      LL z=i==0?y:(Z.back()*B+y)%MOD;
      Y.push_back(y),Z.push_back(z);
      x=(x*B+A)%MOD;
    }
    
//    dumpc(Y);
    trie->release(),delete trie;
    return Z[Q-1];
  }
};

// CUT begin
ifstream data("MojisBag.sample");

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

bool do_test(int Q, int base, int add, int rate, int __expected) {
    time_t startClock = clock();
    MojisBag *instance = new MojisBag();
    int __result = instance->maximumXor(Q, base, add, rate);
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
        int Q;
        from_stream(Q);
        int base;
        from_stream(base);
        int add;
        from_stream(add);
        int rate;
        from_stream(rate);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(Q, base, add, rate, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1555025867;
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
        cout << "MojisBag (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
