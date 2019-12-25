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

#define PI 3.1415926

bool notOOB(vector<string> grid, int x, int y) {
  bool notOOBx = (0 <= x) && (x < grid[0].length());
  bool notOOBy = (0 <= y) && (y < grid.size());
  return (notOOBx && notOOBy);
}

float angle(pair<int, int> location, int otherX, int otherY) {
  return fmod(((atan2(otherY-location.second, otherX-location.first)*180.0/PI) + 450.001), 360.0);
}

int main() {
  vector<string> grid;
  string temp;
  while (cin >> temp) {
    grid.push_back(temp);
  }
  pair<int, int> laserLocation = pair<int, int>(29, 28);
  map<float, deque<pair<int, int>>> angles;
  for (int i = 1; i <= 29; i++) {
    int x = laserLocation.first;
    int y = laserLocation.second-i;
    for (int j = 0; j < i; j++) {
      if (notOOB(grid, x, y) && (grid[y][x] == '#')) {
	angles.emplace(angle(laserLocation, x, y), deque<pair<int, int>>{});
	angles[angle(laserLocation, x, y)].push_back(pair<int, int>(x, y));
      }
      x += 1;
    }
    for (int j = 0; j < 2*i; j++) {
      if (notOOB(grid, x, y) && (grid[y][x] == '#')) {
	angles.emplace(angle(laserLocation, x, y), deque<pair<int, int>>{});
	angles[angle(laserLocation, x, y)].push_back(pair<int, int>(x, y));
      }
      y += 1;
    }
    for (int j = 0; j < 2*i; j++) {
      if (notOOB(grid, x, y) && (grid[y][x] == '#')) {
	angles.emplace(angle(laserLocation, x, y), deque<pair<int, int>>{});
	angles[angle(laserLocation, x, y)].push_back(pair<int, int>(x, y));
      }
      x -= 1;
    }
    for (int j = 0; j < 2*i; j++) {
      if (notOOB(grid, x, y) && (grid[y][x] == '#')) {
	angles.emplace(angle(laserLocation, x, y), deque<pair<int, int>>{});
	angles[angle(laserLocation, x, y)].push_back(pair<int, int>(x, y));
      }
      y -= 1;
    }
    for (int j = 0; j < i; j++) {
      if (notOOB(grid, x, y) && (grid[y][x] == '#')) {
	angles.emplace(angle(laserLocation, x, y), deque<pair<int, int>>{});
	angles[angle(laserLocation, x, y)].push_back(pair<int, int>(x, y));
      }
      x += 1;
    }
  }
  int asteroidNumber = 0;
  while (asteroidNumber < 200) {
    for (map<float, deque<pair<int, int>>>::iterator it = angles.begin(); it != angles.end(); ++it) {
      if (not it->second.empty()) {
	asteroidNumber += 1;
	if (asteroidNumber == 200) {
	  cout << (100 * it->second.front().first) + it->second.front().second << "\n";
	}
	it->second.pop_front();
      }
    }
  }    
  return 0;
}

// So, here's the plan:
// Rotate in a spiral outward from laserLocation calculating angles of the asteroids and putting them into a map<float, deque<pair<int, int>>>
// Then, go through the map, incrementing asteroidNumber and popping the fronts. It should be sorted, so that shouldn't be too hard.
// When asteroidNumber hits 200, do the output thing: (100*xCoord)+yCoord.
