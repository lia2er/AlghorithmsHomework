#pragma once
#include <cmath>
#include <iostream>
#include <vector>
#include <raylib.h>

using namespace std;

void dfs(int node, vector<vector<int>> &graph, vector<bool> &visited) {
  visited[node] = true;
  cout << node + 1 << ' ';
  for (int i = 0; i < graph[node].size(); ++i) 
    if (graph[node][i] == 1 and !visited[i])
      dfs(i, graph, visited);
}

void printGraphMatrix(vector<vector<int>> &graph) {
  cout << "Матриця суміжності" << endl;
  for (int i = 0; i < graph.size(); ++i) {
    for (int j = 0; j < graph[i].size(); ++j) {
      cout << graph[i][j] << ' ';
    }
    cout << endl;
  }
  cout << endl;
}

void dfsAllNodes(vector<vector<int>> &graph) {
  for (int start = 0; start < graph.size(); ++start) {
    cout << "Обхід в глибину вершини " << start + 1 << ':';
    vector<bool> visited(graph.size(), false);
    dfs(start, graph, visited);
    cout << endl;
  }
}

vector<vector<int>> genMatrix(int n) {
  vector<vector<int>> graph(n, vector<int>(n, 0));
  for (int i = 0; i < graph.size(); ++i) {
    for (int j = 0; j < graph[i].size(); ++j)
      graph[i][j] = GetRandomValue(0, 1);
  }
  return graph;
}

void cleanMatrix(vector<vector<int>> &graph) {
  for (int i = 0; i < graph.size(); ++i) {
    for (int j = 0; j < graph[i].size(); ++j) {
      if (graph[i][j] == 1) graph[j][i] = 1;
      else graph[j][i] = 0;
    }
  }
}


void dfsDraw(int node, vector<vector<int>> &graph, vector<bool> &visited, Vector2 pos, float radius, Color color) {
  // do drawing in cirle like `round something. gotta use sinus and cosinus for this
  visited[node] = true;
  DrawCircleV(pos, radius, color);
  int neighbors = graph[node].size();
  float angleStep = (2 * PI) / neighbors;
  for (int i = 0; i < neighbors; ++i) { 
    int neighborIndex = graph[node][i];
    if (neighborIndex == 1 and !visited[neighborIndex]) {
      Vector2 nextPos = {pos.x + cosf(angleStep * i) * 100, pos.y + sinf(angleStep * i) * 100};
      cout << "Node " << node + 1 << " position is: " << nextPos.x << " | " << nextPos.y << endl;
      DrawLineV(pos, nextPos, color);
      dfsDraw(i, graph, visited, nextPos, radius, color);
    }
  }
}

void dfsDrawAllNodes(vector<vector<int>> &graph, Vector2 pos, float radius, Color color, int count) {
  if (graph.empty()) {
    graph = genMatrix(count);
    cleanMatrix(graph);
  }
  for (int start = 0; start < graph.size(); ++start) {
    float angleStep = start * (2 * PI) / count;
    cout << "Обхід в глибину вершини " << start + 1 << ':';
    vector<bool> visited(graph.size(), false);
    dfsDraw(start, graph, visited, pos, radius, color);
    cout << endl;
  }
}
