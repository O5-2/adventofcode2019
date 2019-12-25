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

int main()
{
  map<string, string> orbits;
  string orbited;
  string orbiter;
  while (getline(cin, orbited, ')')) {
    getline(cin, orbiter);
    orbits.insert(pair<string, string>(orbiter, orbited));
  }
  vector<string> santaOrbiteds;
  string santaOrbiter = "SAN";
  while (santaOrbiter != "COM") {
    santaOrbiteds.push_back(santaOrbiter);
    santaOrbiter = orbits[santaOrbiter];
  }
  int transfers = 0;
  string youOrbiter = orbits["YOU"];
  while (find(santaOrbiteds.begin(), santaOrbiteds.end(), youOrbiter) == santaOrbiteds.end()) {
    transfers += 1;
    youOrbiter = orbits[youOrbiter];
  }
  transfers += find(santaOrbiteds.begin(), santaOrbiteds.end(), youOrbiter)-santaOrbiteds.begin()-1;
  cout << transfers << "\n";
  return 0;
}
