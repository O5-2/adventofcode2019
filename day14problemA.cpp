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

int maxHeight(map<string, int> m, map<string, pair<int, vector<pair<string, int>>>> costs) {
  int greatest = 0;
  for (auto& i : m) {
    if (i.second != 0) {
      greatest = max(greatest, height(i.first, costs));
    }
  }
  return greatest;
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
  map<string, int> needed;
  needed.emplace("ORE", 0);
  for (auto& c : costs) {
    needed.emplace(c.first, (c.first == "FUEL"));
  }
  int greatestHeight = height("FUEL", costs);
  while (greatestHeight != 0) {
    for (auto& n : needed) {
      if ((n.second != 0) && (height(n.first, costs) == greatestHeight)) {
	float r = (float)(n.second)/(float)(costs[n.first].first);
	int reactions = ceil(r);
	string nfirst = n.first;
	needed.erase(n.first);
	needed.emplace(nfirst, 0);
	for (auto& c : costs[n.first].second) {
	  int current = needed[c.first];
	  string cfirst = c.first;
	  int csecond = c.second;
	  needed.erase(c.first);
	  needed.emplace(cfirst, current + csecond*reactions);
	}
	// break n.first down into its ingredients
	// use costs[n].second.
	// reactions needed: ceil(n.second/costs[n].first).
	break;
      }
    }
    // "break down" something of height greatestHeight into its ingredients
    greatestHeight = maxHeight(needed, costs);
    // update greatestHeight
  }
  cout << needed["ORE"] << "\n";
  return 0;
}

// Wait a second. Say I can make 1 ORE => 3 A; 2 A => 1 B; 2 A, 2 B => 1 FUEL.
// How do I keep the program from saying "2 A costs 1 ORE, 2 B costs 4 A costs 2 ORE, total cost 3 ORE"?
// And even if I calculate the cost in terms of A, what about
// 1 ORE => 1 A; 1 A => 3 B; 2 B => 1 C; 2 B, 2 C => 1 FUEL.
// Then it'll still naively think "2 B costs 1 A, 2 C costs 4 B costs 2 A, total cost 3 A costs 3 ORE".
// How to fix that?
// Maybe... make a sort of... tree diagram? You have to sort of... "climb down" the tree when you're calculating costs?
// Like, you can't calculate the costs of a chemical X if something created by it, W, hasn't had its cost calculated?
// That would work if it was me. But how do I make a program to do that?
// Perhaps we can simulate it with a single integer "height".
// The height of ORE is 0, and the height of a chemical X is 1 plus the greatest of the heights of its ingredients.
// Would that work?
// Actually, I think it would!
// First step: Make a function int height(string chemical, map<string, pair<int, vector<pair<string, int>>>> costs)
// Second step: ???
// Third step: Output needed["ORE"]. Profit!
