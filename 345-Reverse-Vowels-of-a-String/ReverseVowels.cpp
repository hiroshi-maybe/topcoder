/**
 * 
 * 2/8/2017
 * 
 * 18:38 start
 * 18:45 accepted
 */

// repetition
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define ROF(i,a,b) for(int i=(a);i>=(b);--i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
#define REPS(i,arr)  for(int i=0; i<(arr).size(); ++i)

#define dump(x)  cout << #x << " = " << (x) << endl;
#define dump2(x,y)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cout << endl;

class Solution {
public:
    string reverseVowels(string s) {
        int N = SZ(s);
        int i=0, j = N-1;
        while(i<j) {
            while(i<j && !isVowel(s[i])) i++;
            while(j>i && !isVowel(s[j])) j--;
            
            // invariant: i==j or s[i] and s[j] should be swapped
            swap(s[i++],s[j--]);
        }
        
        return s;
    }
    
    bool isVowel(char _c) {
        char c = tolower(_c);
        return c=='a'||c=='i'||c=='u'||c=='e'||c=='o';
    }
};
