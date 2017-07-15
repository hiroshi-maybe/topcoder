#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>

using namespace std;
#define dumpAR(ar) for(auto &x : (ar)) { cout << x << ','; } cout << endl;

string join(const vector<string> &strs, string delimitor) {
  int L = strs.size();
  if (L==0) { return delimitor; }

  string res = strs[0];
  for(int i=1; i<L; ++i) {
    res += delimitor+strs[i];
  }

  return res;
};

// note that the last empty element is trimmed
vector<string> split(const string &s, char c) {
  vector<string> res;
  
  istringstream ss(s);
  string token;
  while(getline(ss,token,c)) {
    res.push_back(token);
  }
  
  return res;
}

vector<string > split(string s, string del) {
  vector<string> res;
  
  size_t pos = 0;
  while ((pos = s.find(del)) != string::npos) {
    res.push_back(s.substr(0, pos));
    s=s.substr(pos + del.length());
  }
  res.push_back(s);
  
  return res;
}

// test

void assertVec(vector<string> actual, vector<string> expected) {
  assert(actual.size()==expected.size());
  for(int i=0; i<actual.size(); ++i) {
    assert(actual[i]==expected[i]);
  }
}

int main(int argc, char const *argv[]) {
  auto cs0 = split(",", ',');
  assertVec(cs0, {""});

  auto cs1 = split("x", ',');
  assertVec(cs1, {"x"});
  
  auto cs2 = split("x1,y2,z", ',');
  assertVec(cs2, {"x1","y2","z"});
  
  auto cs3 = split("x1,,y2,z,", ',');
  assertVec(cs3, {"x1","","y2","z"});
  
  /*
  auto ss1 = split("x", "**");
  assertVec(ss1, {"x"});
  
  auto ss2 = split("x1**y2**z", "**");
  assertVec(ss2, {"x1","y2","z"});
  
  auto ss3 = split("x1****y2**z**", "**");
  assertVec(ss3, {"x1","","y2","z",""});
  
  assert(join(ss1,",")=="x");
  assert(join(ss2," ")=="x1 y2 z");
  assert(join(ss3,":")=="x1::y2:z:");*/
}
