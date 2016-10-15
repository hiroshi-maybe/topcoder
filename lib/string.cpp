string join(const vector<string> &strs, string delimitor) {
  if (strs.size()==0) { return delimitor; }

  string res = "";
  FORR(s,strs) {
    res += "/"+s;
  }

  return res;
}

vector<string> split(const string &str, char ch) {
  vector<string> ar;

  int i = 0;
  while (i<SZ(str)) {
    string el = "";
    while (str[i]!=ch && i<SZ(str)) {
      el+=str[i];
      i++;
    }
    if (SZ(el)!=0) {
      PUSH(ar, el);
    }
    i++;
  }

  return ar;
}
