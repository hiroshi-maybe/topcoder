#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

string join(const vector<string> &strs, string delimitor) {
  int L = strs.size();
  if (L==0) { return delimitor; }

  string res = strs[0];
  for(int i=1; i<L; ++i) {
    res += delimitor+strs[i];
  }

  return res;
};

vector<string> split(const string &s, char c) {
  vector<string> ar;
  
  string::size_type i = 0;
  string::size_type j = s.find(c);
  
  if(j == string::npos) return {s};
  
  while (j != string::npos) {
    ar.push_back(s.substr(i, j-i));
    i = ++j;
    j = s.find(c, j);
    
    if (j == string::npos)
      ar.push_back(s.substr(i, s.length()));
  }
  
  return ar;
}

// test

void assertVec(vector<string> actual, vector<string> expected) {
  assert(actual.size()==expected.size());
  for(int i=0; i<actual.size(); ++i) {
    assert(actual[i]==expected[i]);
  }
}

int main(int argc, char const *argv[]) {
  auto ss1 = split("x", ',');
  assertVec(ss1, {"x"});
  
  auto ss2 = split("x1,y2,z", ',');
  assertVec(ss2, {"x1","y2","z"});
  
  auto ss3 = split("x1,,y2,z,", ',');
  assertVec(ss3, {"x1","","y2","z",""});
  
  assert(join(ss1,",")=="x");
  assert(join(ss2," ")=="x1 y2 z");
  assert(join(ss3,":")=="x1::y2:z:");
}
