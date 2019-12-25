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

int gcd(int a, int b) {
  if ((a == 0) || (b == 0)) {
    return a+b;
  } else if (a >= b) {
    return gcd(b, a % b);
  }
  return gcd(a, b % a);
}

int visibleAsteroids(vector<string> grid, pair<int, int> position) {
  int total = 0;
  for (int x = 0; x < grid[0].length(); x++) {
    for (int y = 0; y < grid.size(); y++) {
      if (grid[y][x] == '#') {
	bool visible = true;
	int gcdDistances = gcd(abs(x-position.first), abs(y-position.second));
	for (int i = 1; i < gcdDistances; i++) {
	  if (grid[position.second+(i*(y-position.second)/gcdDistances)][position.first+(i*(x-position.first)/gcdDistances)] == '#') {
	    visible = false;
	  }
	}
	total += visible;
      }
    }
  }
  return total;
}

int main()
{
  vector<string> grid;
  string temp;
  while (cin >> temp) {
    grid.push_back(temp);
  }
  pair<int, int> maxLocation;
  int maxVisible = 0;
  for (int stationX = 0; stationX < grid[0].length(); stationX++) {
    for (int stationY = 0; stationY < grid.size(); stationY++) {
      if (grid[stationY][stationX] == '#') {
	int visible = visibleAsteroids(grid, pair<int, int>(stationX, stationY));
	if (maxVisible < visible) {
	  maxVisible = visible;
	  maxLocation = pair<int, int>(stationX, stationY);
	}
      }
    }
  }
  cout << maxLocation.first << " " << maxLocation.second << "\n" << maxVisible-1 << "\n";
  return 0;
}
