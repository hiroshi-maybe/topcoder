string join(const vector<string> &strs, string delimitor) {
  int L = strs.size();
  if (L==0) { return delimitor; }

  string res = strs[0];
  FOR(i,1,L) {
    res += delimitor+strs[i];
  }

  return res;
};

vector<string> split(const string &s, char c) {
  vector<string> ar;

  string::size_type i = 0;
  string::size_type j = s.find(c);

  while (j != string::npos) {
    ar.push_back(s.substr(i, j-i));
    i = ++j;
    j = s.find(c, j);

    if (j == string::npos)
      ar.push_back(s.substr(i, s.length()));
  }

  return ar;
}
