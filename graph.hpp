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

// i can draw two edges at a time and count them so they wont redraw
void dfsDraw(int node, vector<vector<int>> &graph, vector<bool> &visited, Vector2 pos, float distance) {
    visited[node] = true;

    // Draw the current node circle
    DrawCircleV(pos, 20, MAROON);
    DrawText(TextFormat("%d", node), (int)pos.x - 5, (int)pos.y - 5, 20, WHITE);

    int totalNodes = graph.size();
    
    for (int i = 0; i < totalNodes; ++i) {
        // Only proceed if there is a connection AND we haven't been there
        if (graph[node][i] == 1 && !visited[i]) {
            
            // Calculate direction based on neighbor index
            // Using i * (2*PI / totalNodes) ensures neighbors 
            // spread out in different directions
            float angle = i * (2.0f * PI / totalNodes);
            
            Vector2 nextPos = {
                pos.x + cosf(angle) * distance,
                pos.y + sinf(angle) * distance
            };

            // Draw the line BEFORE recursing
            DrawLineV(pos, nextPos, BLACK);

            // Recurse to the next node
            dfsDraw(i, graph, visited, nextPos, distance * 0.8f);
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
    dfsDraw(start, graph, visited, pos, 100);
    cout << endl;
  }
}
