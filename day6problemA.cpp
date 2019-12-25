#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>

#include <cmath>
#include <iomanip>
#include <array>

using namespace std;

map<string, int> depths;

int depth(map<string, string> parents, string s) {
  if (s == "COM") {
    return 0;
  } else if (depths.find(s) != depths.end()) {
    return depths[s];
  }
  int recur = 1+depth(parents, parents[s]);
  depths.insert(pair<string, int>(s, recur));
  return recur;
}

int main()
{
  map<string, string> orbits;
  string orbited;
  string orbiter;
  depths.insert(pair<string, int>("COM", 0));
  while (getline(cin, orbited, ')')) {
    getline(cin, orbiter);
    orbits.insert(pair<string, string>(orbiter, orbited));
  }
  int total = 0;
  for (map<string, string>::iterator it = orbits.begin(); it != orbits.end(); ++it) {
    total += depth(orbits, it->first);
  }   
  cout << total << "\n";
  return 0;
}
