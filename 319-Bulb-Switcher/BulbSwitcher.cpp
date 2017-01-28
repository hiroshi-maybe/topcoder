/**
 * 
 * 1/27/2017
 * 
 * 19:06 start
 * 19:27 TLE for 99999 by O(n^2)
 * 19:34 TLE for 999999
 * 19:45 accepted by O(log n)
 * 19:52 add solution by O(1) inspired by https://discuss.leetcode.com/topic/31929/math-solution
 */

// debug cout
#define dump(x)  cout << #x << " = " << (x) << endl;
#define dump2(x,y)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cout << endl;

class Solution {
public:
    int bulbSwitch(int n) {
        return sqrt(n);
    }
};

class Solution_v1 {
public:
    int bulbSwitch(int n) {
        if (n<=0) return 0;
        int k=1;
        while(n>0) {
            int m = 2*k+1;
            n -= m;
            k++;
        }
        
        return k-1;
    }
};

class Solution_TLE {
public:
    int bulbSwitch(int n) {
        if (n<=0) return 0;
        int res = 1;
        for(int k=2; k<=n; k++) {
            int count = 0;
            for(int p=1; p*p<=k; p++) {
                if (k%p==0) {
                    if (p*p==k) count += 1;
                    else count += 2;
                }
            }
            if (count%2==1) res++;
        }
        
        return res;
    }
};
