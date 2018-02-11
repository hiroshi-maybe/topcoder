#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>

using namespace std;
/*
 
 Union-find algorithm, O(α(N)) time per operation
 
  - Popular algorithm to manage disjoint set
 
 References:
  - https://en.wikipedia.org/wiki/Disjoint-set_data_structure
  - Ant book 2-4 data structures
  - CLRS 21 Data Structures for Disjoint Sets
 
 Usage:
 
  UF uf(10);
  uf.unite(0,1);
  uf.unite(1,2);
  cout << uf.same(0,1) << endl; // true
 
 */

struct UF {
public:
  int groupNum;
  UF(int N) {
    uf=vector<int>(N);
    rank=vector<int>(N);
    for(int i=0; i<N; ++i) uf[i]=i,rank[i]=0;
    groupNum=N;
  }
  
  int find(int i) {
    return uf[i]==i?i:uf[i]=find(uf[i]);
  }
  
  bool same(int x, int y) {
    return find(x)==find(y);
  }
  
  void unite(int x, int y) {
    x=find(x);
    y=find(y);
    if(x==y) return;
    groupNum--;
    
    if (rank[x]==rank[y]) {
      uf[x]=y;
      rank[y]++;
      return;
    }
    
    if (rank[x]<rank[y]) {
      uf[x]=y;
    } else {
      uf[y] =x;
      if(rank[x]==rank[y]) ++rank[x];
    }
  }
private:
  vector<int> rank;
  vector<int> uf;
};

int main(int argc, char const *argv[]) {
  UF uf(10);
  uf.unite(1,3);
  assert(uf.same(1,3));
  assert(uf.groupNum==9);
  uf.unite(4,6);
  uf.unite(0,2);
  uf.unite(7,8);
  uf.unite(0,1);
  uf.unite(4,5);
  uf.unite(1,2);
  assert(uf.same(0,3));
  assert(uf.same(4,6));
  assert(uf.same(7,8));
  assert(uf.groupNum==4);
}
