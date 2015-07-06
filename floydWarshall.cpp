#include <vector>
#include <string>
using namespace std;

// Get All pair shortest path
// Update "edgeNum x edgeNum" table of all pair-wise distances by O(∣V∣^3)
vector<vector<int>> floydWarshall(vector<vector<int>> dist, int edgeNum) {
  for (int k = 0; k < edgeNum; k++) {
    for (int i = 0; i < edgeNum; i++) {
      for (int j = 0; j < edgeNum; j++) {
	dist[i][j] = std::min( dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
  return dist;
}
