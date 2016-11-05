/********** union-find lib **********/

int groupNum;
vector < int > rank;
vector < int > parent;
void initUnionSet(int n) {
  groupNum = n+1;
  rank = vector < int >(n+1);
  parent = vector < int >(n+1);
  for(int i=0; i<=n; i++) {
    rank[i]=0;
    parent[i]=i;
  }
}

int find(int n) {
  while(n != parent[n]) {
    // shorten path
    parent[n] = parent[parent[n]];
    n = parent[n];
  }

  return n;
}

bool unioned(int p, int q) {
  return find(p)==find(q);
}

void dounion(int p, int q) {
  int n = find(p);
  int m = find(q);

  if (n==m) return;

  groupNum--;

  if (rank[n]==rank[m]) {
    parent[n] = m;
    rank[m]++;
    return;
  }

  if (rank[n]<rank[m]) {
    parent[n] = m;
  } else {
    parent[m] = n;
  }
}
