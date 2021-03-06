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

pair<int, int> advance(pair<int, int> previous, char direction, int steps) {
  pair<int, int> current;
  if (direction == 'U') {
    current = pair<int, int>(previous.first, previous.second+steps);
  } else if (direction == 'R') {
    current = pair<int, int>(previous.first+steps, previous.second);
  } else if (direction == 'L') {
    current = pair<int, int>(previous.first-steps, previous.second);
  } else {
    current = pair<int, int>(previous.first, previous.second-steps);
  }
  return current;
}

int intersection(pair<int, int> firstBegin, pair<int, int> firstEnd, pair<int, int> secondBegin, pair<int, int> secondEnd) {
  // First we check to see which is horizontal and which is vertical.
  if ((firstBegin.first == firstEnd.first) && (secondBegin.second == secondEnd.second)) {
    // Then we check to see if the x coordinate of first is between the x coordinates of second.
    if (((secondBegin.first <= firstBegin.first) && (firstBegin.first <= secondEnd.first)) || ((secondEnd.first <= firstBegin.first) && (firstBegin.first <= secondBegin.first))) {
      // Then we check to see if the y coordinate of second is between the y coordinates of first.
      if (((firstBegin.second <= secondBegin.second) && (secondBegin.second <= firstEnd.second)) || ((firstEnd.second <= secondBegin.second) && (secondBegin.second <= firstBegin.second))) {
	return abs(secondBegin.first-firstBegin.first)+abs(firstBegin.second-secondBegin.second); // Does this work?
	//pair<int, int>(firstBegin.first, secondBegin.second);
      }
    }
  } else if ((firstBegin.second == firstEnd.second) && (secondBegin.first == secondEnd.first)) {
    // Then we check to see if the x coordinate of second is between the x coordinates of first.
    if (((firstBegin.first <= secondBegin.first) && (secondBegin.first <= firstEnd.first)) || ((firstEnd.first <= secondBegin.first) && (secondBegin.first <= firstBegin.first))) {
      // Then we check to see if the y coordinate of first is between the y coordinates of second.
      if (((secondBegin.second <= firstBegin.second) && (firstBegin.second <= secondEnd.second)) || ((secondEnd.second <= firstBegin.second) && (firstBegin.second <= secondBegin.second))) {
	return abs(firstBegin.first-secondBegin.first)+abs(secondBegin.second-firstBegin.second); // Does this work?
	//pair<int, int>(secondBegin.first, firstBegin.second);
      }
    }
  }
  // If it fails any of those checks, we return -1.
  return -1;
}

int main()
{
  vector<pair<int, int>> firstWire;
  vector<pair<int, int>> secondWire;
  firstWire.push_back(pair<int, int>(0, 0));
  secondWire.push_back(pair<int, int>(0, 0));
  char direction;
  int steps;
  vector<int> firstDistances;
  vector<int> secondDistances;
  while (cin >> direction) {
    cin >> steps;
    firstDistances.push_back(steps);
    firstWire.push_back(advance(firstWire[firstWire.size()-1], direction, steps));
    cin >> direction;
    if (direction != ',') {
      break;
    }
  }
  do {
    cin >> steps;
    secondDistances.push_back(steps);
    secondWire.push_back(advance(secondWire[secondWire.size()-1], direction, steps));
    cin >> direction;
  } while (cin >> direction);
  vector<int> intersectionSteps;
  int firstSteps = 0;
  for (int i = 1; i < firstWire.size()-1; i++) {
    firstSteps += firstDistances[i-1];
    int secondSteps = 0;
    for (int j = 1; j < secondWire.size()-1; j++) {
      secondSteps += secondDistances[j-1];
      int partialSteps = intersection(firstWire[i], firstWire[i+1], secondWire[j], secondWire[j+1]);
      if (partialSteps != -1) {
	intersectionSteps.push_back(firstSteps+secondSteps+partialSteps);
      }
    }
  }
  int minDistance = 1000000000;
  for (int i = 0; i < intersectionSteps.size(); i++) {
    minDistance = min(minDistance, intersectionSteps[i]);
  }
  cout << minDistance << "\n";
  return 0;
}
