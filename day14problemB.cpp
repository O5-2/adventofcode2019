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

string removeComma(string s) {
  if (s[s.length()-1] == ',') {
    return s.substr(0, s.length()-1);
  }
  return s;
}

int height(string chemical, map<string, pair<int, vector<pair<string, int>>>> costs) {
  if (chemical == "ORE") {
    return 0;
  }
  int maxIngredientHeight = 0;
  for (auto p : costs[chemical].second) {
    maxIngredientHeight = max(maxIngredientHeight, height(p.first, costs));
  }
  return maxIngredientHeight+1;
}

int maxHeight(map<string, long long int> m, map<string, pair<int, vector<pair<string, int>>>> costs) {
  int greatest = 0;
  for (auto& i : m) {
    if (i.second != 0) {
      greatest = max(greatest, height(i.first, costs));
    }
  }
  return greatest;
}

long long int neededOre(int wantedFuel, map<string, pair<int, vector<pair<string, int>>>> costs) {
  // How to lengthen r?
  map<string, long long int> needed;
  needed.emplace("ORE", 0);
  for (auto& c : costs) {
    needed.emplace(c.first, wantedFuel*(c.first == "FUEL")); // Does this work?
  }
  int greatestHeight = height("FUEL", costs);
  while (greatestHeight != 0) {
    for (auto& n : needed) {
      if ((n.second != 0) && (height(n.first, costs) == greatestHeight)) {
	long double r = (long double)(n.second)/(long double)(costs[n.first].first);
	long long int reactions = ceil(r);
	string nfirst = n.first;
	needed.erase(n.first);
	needed.emplace(nfirst, 0);
	for (auto& c : costs[n.first].second) {
	  long long int current = needed[c.first];
	  string cfirst = c.first;
	  long long int csecond = c.second;
	  needed.erase(c.first);
	  needed.emplace(cfirst, current + csecond*reactions);
	}
	break;
      }
    }
    greatestHeight = maxHeight(needed, costs);
  }
  return needed["ORE"];
}

int main()
{
  map<string, pair<int, vector<pair<string, int>>>> costs;
  int ingredientCost;
  while (cin >> ingredientCost) {
    string ingredientName;
    cin >> ingredientName;
    vector<pair<string, int>> ingredients;
    ingredients.push_back(pair<string, int>(removeComma(ingredientName), ingredientCost));
    while (ingredientName[ingredientName.length()-1] == ',') {
      cin >> ingredientCost >> ingredientName;
      ingredients.push_back(pair<string, int>(removeComma(ingredientName), ingredientCost));
    }
    string junk;
    cin >> junk;
    int resultProduced;
    string resultName;
    cin >> resultProduced >> resultName;
    costs.emplace(resultName, pair<int, vector<pair<string, int>>>(resultProduced, ingredients));
  }
  long long int low = 1;
  long long int high = 1000000000000;
  int result;
  int mid;
  while (low+1 < high) {
    mid = (low+high)/2;
    cout << mid << "\n"; // DEBUG
    if (neededOre(mid, costs) > 1000000000000) {
      high = mid;
    } else {
      low = mid;
    }
  }
  cout << mid-1 << "\n";
  return 0;
}

// I frankly have no idea how to solve this.

// Maybe... calculate the amount of leftover chemicals after dividing one trillion by 598038, and see how much fuel can be made from that?
// But how do I do so?
// Maybe... put the fuel calculation thing into a while loop, and as soon as ORE goes negative, stop?
// That might work.
// Take the simplest case: 1 ORE => 2 A; 1 A => 1 FUEL. How to calculate that?
// Well, using X ore produces 2X A produces 2X FUEL. But that's not really an algorithm, and it'd be a lot more complicated.
// And what about 1 ORE => 100 A; 1 ORE => 1 B; 1 A, 1 B => 1 FUEL.

// r/adventofcode is apparently using a binary search somehow.
// Oh, I think I get what they mean!
// Looks like I don't have to significantly modify my code after all.
