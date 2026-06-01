#pragma once
#include <cmath>
#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <raylib.h>
#include <functional>

using namespace std;

void dfs(int node, vector<vector<int>> &graph, vector<bool> &visited) {
  visited[node] = true;
  cout << node + 1 << ' ';
  for (int i = 0; i < graph[node].size(); ++i) 
    if (graph[node][i] == 1 and !visited[i])
      dfs(i, graph, visited);
}

void bfs(int start, vector<vector<int>> &graph, vector<bool> &visited) {
  queue<int> q;
  q.push(start);
  visited[start] = true;
  while (!q.empty()) {
    int current = q.front();
    q.pop();
    cout << current + 1 << ' ';
    for (int i = 0; i < (int)graph[current].size(); ++i)
      if (graph[current][i] == 1 && !visited[i]) {
        q.push(i);
        visited[i] = true;
      }
  }
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

void printWeightMatrix(vector<vector<int>> graph) {
  cout << "Матриця ваг" << endl;
  for (int i = 0; i < graph.size(); ++i) {
    for (int j = 0; j < graph[i].size(); ++j)
      cout << graph[i][j] << ' ';
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

void bfsAllNodes(vector<vector<int>> &graph) {
  for (int start = 0; start < (int)graph.size(); ++start) {
    cout << "Обхід в ширину вершини " << start + 1 << ':';
    vector<bool> visited(graph.size(), false);
    bfs(start, graph, visited);
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
      if (graph[i][j] == 1)
      { 
        graph[i][j] = 1;
        graph[j][i] = graph[i][j];
      }
    }
  }
}

vector<vector<int>> genWeights(vector<vector<int>> &graph) {
  for (int i = 0; i < graph.size(); ++i) {
    for (int j = 0; j < graph[i].size(); ++j)
    {
      if (graph[i][j] == 1)
      {
        graph[i][j] = GetRandomValue(1, 100);
        graph[j][i] = graph[i][j];
      }
    }
  }
  return graph;
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

int findMinVertex(int vertices, vector<int> &key, vector<bool> &mstSet)
{
  int minKey = INT_MAX;
  int minVertex = -1;

  for (int v = 0; v < vertices; ++v)
  {
    if (!mstSet[v] and key[v] < minKey)
    {
      minKey = key[v];
      minVertex = v;
    }
  }
  return minVertex;
}

void printMST(vector<int> &parent, vector<vector<int>> &graph, int vertices)
{
  cout << "Minimal Spaning Tree: \n";
  for (int i = 1; i < vertices; ++i)
    cout << parent[i] + 1 << " - " << i + 1 << " weight: " << graph[i][parent[i]] << endl;
}

void primMST(vector<vector<int>> &graph, int vertices)
{
  vector<int> parent(vertices);
  vector<int> key(vertices, INT_MAX);
  vector<bool> mstSet(vertices, false);

  key[0] = 0;
  parent[0] = -1;

  for (int count = 0; count < vertices - 1; ++count)
  {
    int u = findMinVertex(vertices, key, mstSet);
    mstSet[u] = true;

    for (int v = 0; v  < vertices; ++v)
    {
      if (graph[u][v] and !mstSet[v] and graph[u][v] < key[v])
      {
        parent[v] = u;
        key[v] = graph[u][v];
      }
    }
  }
  printMST(parent, graph, vertices);
}

int findMinDist(vector<int> &distance, vector<bool> &visited, int vertices)
{
  int minVertex = -1;
  for (int v = 0; v < vertices; ++v)
  {
    if (!visited[v] && (minVertex == -1 || distance[v] < distance[minVertex]))
      minVertex = v;
  }
  return minVertex;
}

void dijkstra(vector<vector<int>> &graph, int start, int vertices)
{
  vector<int> distance(vertices, INT_MAX);
  vector<bool> visited(vertices, false);

  distance[start] = 0;

  for (int count = 0; count < vertices - 1; ++count)
  {
    int u = findMinDist(distance, visited, vertices);
    visited[u] = true;

    for (int v = 0; v < vertices; ++v)
    {
      if (!visited[v] && graph[u][v] && distance[u] != INT_MAX &&
        distance[u] + graph[u][v] < distance[v])
        distance[v] = distance[u] + graph[u][v];
    }
  }

  cout << "Найкоротші відстані від вершини " << start + 1 << ":" << endl;
  for (int i = 0; i < vertices; ++i)
    cout << "Вершина " << i + 1 << ": " << distance[i] << endl;
}


// Kruskal
struct KEdge {
  int a, b, weight;
  bool operator<(const KEdge &other) const { return weight < other.weight; }
};

int kFind(vector<int> &parent, int i) {
  if (parent[i] == -1) return i;
  return kFind(parent, parent[i]);
}

void kUnion(vector<int> &parent, int x, int y) {
  parent[kFind(parent, x)] = kFind(parent, y);
}

vector<KEdge> kruskalMST(int n, vector<KEdge> edges) {
  sort(edges.begin(), edges.end());
  vector<int> parent(n, -1);
  vector<KEdge> result;
  int totalWeight = 0;
  for (KEdge &e : edges) {
    int x = kFind(parent, e.a);
    int y = kFind(parent, e.b);
    if (x != y) {
      result.push_back(e);
      kUnion(parent, x, y);
      totalWeight += e.weight;
    }
  }
  return result;
}

struct GraphNode {
  Vector2 pos;
  string label;
};

struct GraphEdge {
  int a, b;
  int weight;
  bool inResult;
};

enum GraphMode {
  IDLE,
  ADD_NODE,
  ADD_EDGE_A,
  ADD_EDGE_B,
  REMOVE,
};

enum GraphAlgo {
  NONE,
  DFS,
  BFS,
  KRUSKAL,
};

struct GraphState {
  vector<GraphNode> nodes;
  vector<GraphEdge> edges;

  GraphMode mode = IDLE;
  GraphAlgo algo = NONE;
  int edgeStartA = -1;
  int selectedNode = -1;
  bool dragging = false;
  Vector2 dragOffset = {0, 0};

  int algoStart = 0;
  string visitOrder;
  int mstTotalWeight = 0;
  string pendingWeight;
};

int GNodeAt(const vector<GraphNode> &nodes, Vector2 p, float r = 20.f) {
  for (int i = 0; i < (int)nodes.size(); i++) {
    float dx = nodes[i].pos.x - p.x, dy = nodes[i].pos.y - p.y;
    if (sqrtf(dx*dx + dy*dy) <= r) return i;
  }
  return -1;
}

int GFindEdge(const vector<GraphEdge> &edges, int a, int b) {
  for (int i = 0; i < (int)edges.size(); i++)
    if ((edges[i].a==a && edges[i].b==b) || (edges[i].a==b && edges[i].b==a))
      return i;
  return -1;
}

vector<vector<int>> GBuildAdj(int n, const vector<GraphEdge> &edges) {
  vector<vector<int>> adj(n);
  for (auto &e : edges) {
    adj[e.a].push_back(e.b);
    adj[e.b].push_back(e.a);
  }
  for (auto &v : adj) sort(v.begin(), v.end());
  return adj;
}

void GClearResult(GraphState &g) {
  for (auto &e : g.edges) e.inResult = false;
  g.visitOrder = "";
  g.mstTotalWeight = 0;
  g.algo = NONE;
}

void GRunDFS(GraphState &g) {
  GClearResult(g);
  g.algo = DFS;
  int n = (int)g.nodes.size();
  if (n == 0) return;
  auto adj = GBuildAdj(n, g.edges);
  vector<bool> visited(n, false);
  string order;

  function<void(int)> rec = [&](int node) {
    visited[node] = true;
    if (!order.empty()) order += " > ";
    order += g.nodes[node].label;
    for (int nb : adj[node]) {
      if (!visited[nb]) {
        int ei = GFindEdge(g.edges, node, nb);
        if (ei >= 0) g.edges[ei].inResult = true;
        rec(nb);
      }
    }
  };

  rec(g.algoStart);
  g.visitOrder = "DFS: " + order;
}

void GRunBFS(GraphState &g) {
  GClearResult(g);
  g.algo = BFS;
  int n = (int)g.nodes.size();
  if (n == 0) return;
  auto adj = GBuildAdj(n, g.edges);
  vector<bool> visited(n, false);
  string order;

  queue<int> q;
  q.push(g.algoStart);
  visited[g.algoStart] = true;
  while (!q.empty()) {
    int cur = q.front(); q.pop();
    if (!order.empty()) order += " > ";
    order += g.nodes[cur].label;
    for (int nb : adj[cur]) {
      if (!visited[nb]) {
        visited[nb] = true;
        int ei = GFindEdge(g.edges, cur, nb);
        if (ei >= 0) g.edges[ei].inResult = true;
        q.push(nb);
      }
    }
  }
  g.visitOrder = "BFS: " + order;
}

void GRunKruskal(GraphState &g) {
  GClearResult(g);
  g.algo = KRUSKAL;
  int n = (int)g.nodes.size();
  if (n == 0) return;

  vector<KEdge> kedges;
  for (int i = 0; i < (int)g.edges.size(); i++) {
    int w = (g.edges[i].weight > 0) ? g.edges[i].weight : 1;
    kedges.push_back({g.edges[i].a, g.edges[i].b, w});
  }

  vector<KEdge> mst = kruskalMST(n, kedges);
  int total = 0;
  for (auto &ke : mst) {
    int ei = GFindEdge(g.edges, ke.a, ke.b);
    if (ei >= 0) g.edges[ei].inResult = true;
    total += ke.weight;
  }
  g.mstTotalWeight = total;
  g.visitOrder = "MST weight: " + to_string(total)
               + "  (" + to_string((int)mst.size()) + " edges)";
}

void GInitExample(GraphState &g, Color /*unused*/) {
  g.nodes = {
    {{560, 430}, "1"},
    {{420, 330}, "2"},
    {{560, 230}, "3"},
    {{420, 130}, "4"},
    {{700, 230}, "5"},
  };
  g.edges = {
    {0,1,9,false}, {0,2,75,false}, {0,4,42,false},
    {1,2,95,false}, {1,3,19,false},
    {2,3,51,false}, {2,4,66,false},
  };
  GClearResult(g);
}

void GUpdate(GraphState &g, Vector2 mouse, float /*dt*/,
             Rectangle canvasRect,
             Color /*colVisited*/, Color /*colCurrent*/, Color /*defaultNodeColor*/)
{
  if (g.dragging) {
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && g.selectedNode >= 0)
      g.nodes[g.selectedNode].pos = {mouse.x - g.dragOffset.x, mouse.y - g.dragOffset.y};
    else
      g.dragging = false;
    return;
  }

  if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) return;

  bool inCanvas = CheckCollisionPointRec(mouse, canvasRect);
  int hit = GNodeAt(g.nodes, mouse);

  if (g.mode == ADD_NODE) {
    if (inCanvas) {
      int idx = (int)g.nodes.size();
      g.nodes.push_back({mouse, to_string(idx + 1)});
      GClearResult(g);
    }

  } else if (g.mode == ADD_EDGE_A) {
    if (hit >= 0) { g.edgeStartA = hit; g.mode = ADD_EDGE_B; }

  } else if (g.mode == ADD_EDGE_B) {
    if (hit >= 0 && hit != g.edgeStartA
        && GFindEdge(g.edges, g.edgeStartA, hit) < 0) {
      int w = 0;
      if (!g.pendingWeight.empty()) {
        try { w = stoi(g.pendingWeight); } catch (...) { w = 0; }
      }
      g.edges.push_back({g.edgeStartA, hit, w, false});
      g.pendingWeight = "";
      GClearResult(g);
    }
    g.mode = ADD_EDGE_A;
    g.edgeStartA = -1;

  } else if (g.mode == REMOVE) {
    if (hit >= 0) {
      g.edges.erase(remove_if(g.edges.begin(), g.edges.end(),
        [hit](const GraphEdge &e){ return e.a==hit || e.b==hit; }), g.edges.end());
      for (auto &e : g.edges) {
        if (e.a > hit) e.a--;
        if (e.b > hit) e.b--;
      }
      g.nodes.erase(g.nodes.begin() + hit);
      for (int i = 0; i < (int)g.nodes.size(); i++)
        g.nodes[i].label = to_string(i + 1);
      if (g.algoStart >= (int)g.nodes.size())
        g.algoStart = max(0, (int)g.nodes.size() - 1);
      g.selectedNode = -1;
      GClearResult(g);
    } else if (inCanvas) {
      for (int i = 0; i < (int)g.edges.size(); i++) {
        Vector2 a = g.nodes[g.edges[i].a].pos;
        Vector2 b = g.nodes[g.edges[i].b].pos;
        float dx = b.x-a.x, dy = b.y-a.y, len2 = dx*dx+dy*dy;
        float t = len2 > 0 ? ((mouse.x-a.x)*dx+(mouse.y-a.y)*dy)/len2 : 0;
        t = max(0.f, min(1.f, t));
        float ex = a.x+t*dx-mouse.x, ey = a.y+t*dy-mouse.y;
        if (sqrtf(ex*ex+ey*ey) < 8.f) {
          g.edges.erase(g.edges.begin() + i);
          GClearResult(g);
          break;
        }
      }
    }

  } else {
    if (hit >= 0) {
      g.selectedNode = hit;
      g.dragOffset = {mouse.x - g.nodes[hit].pos.x, mouse.y - g.nodes[hit].pos.y};
      g.dragging = true;
    } else {
      g.selectedNode = -1;
    }
  }
}

void GDraw(const GraphState &g, Vector2 mouse,
           Color colEdge, Color colEdgeResult,
           Color colNode, Color colSelected, Color colLabel)
{
  const float R = 18.f;

  for (int i = 0; i < (int)g.edges.size(); i++) {
    Vector2 a = g.nodes[g.edges[i].a].pos;
    Vector2 b = g.nodes[g.edges[i].b].pos;
    Color c = g.edges[i].inResult ? colEdgeResult : colEdge;
    float t = g.edges[i].inResult ? 3.f : 2.f;
    DrawLineEx(a, b, t, c);

    if (g.edges[i].weight > 0) {
      Vector2 mid = {(a.x+b.x)/2.f - 8, (a.y+b.y)/2.f - 8};
      string wl = to_string(g.edges[i].weight);
      DrawText(wl.c_str(), (int)mid.x, (int)mid.y, 14, colLabel);
    }
  }

  if (g.mode == ADD_EDGE_B && g.edgeStartA >= 0)
    DrawLineEx(g.nodes[g.edgeStartA].pos, mouse, 1.5f, {200,200,100,140});

  for (int i = 0; i < (int)g.nodes.size(); i++) {
    Vector2 p = g.nodes[i].pos;
    Color fill = colNode;
    if (i == g.selectedNode && g.mode == IDLE) fill = colSelected;
    if (i == g.edgeStartA && g.mode == ADD_EDGE_B) fill = colSelected;
    if (i == g.algoStart && g.algo != NONE) fill = colSelected;
    DrawCircleV(p, R, fill);
    DrawCircleLines((int)p.x, (int)p.y, (int)R, {200,220,255,160});
    int tw = MeasureText(g.nodes[i].label.c_str(), 16);
    DrawText(g.nodes[i].label.c_str(), (int)(p.x-tw/2), (int)(p.y-8), 16, colLabel);
  }
}
