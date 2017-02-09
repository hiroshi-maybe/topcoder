/**
 * 
 * 2/8/2017
 * 
 * 20:10 start
 * 20:18 wrong for "ababffzzeee",2
 * 20:19 wrong for "a",0
 * 20:37 accepted
 * 
 * 23:38 keep adding variable solutions
 */

typedef vector < bool > VB;
typedef vector < int > VI;
typedef vector < string > VS;
typedef vector < vector < int > > VVI;
typedef unordered_map < char, int > MAPCI;
typedef unordered_map < int, int > MAPII;
typedef unordered_map < string, int > MAPSI;
typedef unordered_set < int > SETI;
typedef unordered_set < string > SETS;

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define ROF(i,a,b) for(int i=(a);i>=(b);--i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
#define REPS(i,arr)  for(int i=0; i<(arr).size(); ++i)

// debug cout
#define dump(x)  cout << #x << " = " << (x) << endl;
#define dump2(x,y)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cout << endl;

class Solution_v3 {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        MAPCI CS;
        int res = 0, N = SZ(s);
        int l=0, r=0;
        while(r<N) {
            while (SZ(CS)<=k&&r<N) {
                res = max(res, r-l);
                CS[s[r++]]++;
            }
            while (SZ(CS)>k&&l<N) {
                if (--CS[s[l++]] == 0) CS.erase(s[l-1]);
            }
            
            // CS keeps chars in s[l..<r]
            if (SZ(CS)<=k) res = max(res, r-l);
        }
        
        return res;
    }
};

class Solution_v2 {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        MAPCI CS;
        int res = 0, N = SZ(s);
        for(int l=0, r=0; r<N; ) {
            if (SZ(CS)>k) {
                char c = s[l++];
                if (--CS[c]==0) CS.erase(c);
            } else {
                CS[s[r++]]++;
            }
            
            // CS keeps chars for s[l..<r]
            if (SZ(CS)<=k) res = max(res, r-l);
        }
        
        return res;
    }
};

class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        MAPCI CS;
        int N = SZ(s);
        int res = 0;
        for(int l=0, r=0; r<N; ++r) {
            ++CS[s[r]];
            
            while(SZ(CS)>k) {
                if (--CS[s[l]] == 0) CS.erase(s[l]);
                l++;
            }
            
            // CS keeps chars for s[l...r]
            res = max(res, r-l+1);
        }
        
        return res;
    }
};
