#pragma once
#include <cmath>
#include <iostream>
#include <vector>
#include <climits>
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
// ─── Visual graph state ───────────────────────────────────────────────────────

struct GraphNode {
  Vector2 pos;
  string  label;
};

struct GraphEdge {
  int  a, b;
  bool isTree;
  bool active;
};

enum GraphMode {
  GMODE_IDLE,
  GMODE_ADD_NODE,
  GMODE_ADD_EDGE_A,
  GMODE_ADD_EDGE_B,
  GMODE_REMOVE,
  GMODE_RUN_DFS,
};

struct DFSStep {
  int  node;
  int  edgeIdx;
  bool isTree;
  bool backtrack;
};

struct GraphState {
  vector<GraphNode> nodes;
  vector<GraphEdge> edges;

  GraphMode mode = GMODE_IDLE;
  int edgeStartA = -1;
  int selectedNode = -1;
  bool dragging = false;
  Vector2 dragOffset = {0, 0};

  int dfsStart = 0;
  vector<DFSStep> dfsSteps;
  int dfsStepIdx = -1;
  float dfsTimer = 0.f;
  bool dfsPaused = false;
  vector<bool>  dfsVisited;
  vector<Color> nodeColors;
  string visitOrder;
};

static int GNodeAt(const vector<GraphNode> &nodes, Vector2 p, float r = 20.f) {
  for (int i = 0; i < (int)nodes.size(); i++) {
    float dx = nodes[i].pos.x - p.x, dy = nodes[i].pos.y - p.y;
    if (sqrtf(dx*dx + dy*dy) <= r) return i;
  }
  return -1;
}

static int GFindEdge(const vector<GraphEdge> &edges, int a, int b) {
  for (int i = 0; i < (int)edges.size(); i++)
    if ((edges[i].a==a && edges[i].b==b) || (edges[i].a==b && edges[i].b==a))
      return i;
  return -1;
}

static vector<vector<int>> GBuildAdj(int n, const vector<GraphEdge> &edges) {
  vector<vector<int>> adj(n);
  for (auto &e : edges) { adj[e.a].push_back(e.b); adj[e.b].push_back(e.a); }
  for (auto &v : adj) sort(v.begin(), v.end());
  return adj;
}

static vector<DFSStep> GGenDFS(int start, int n,
    const vector<vector<int>> &adj, const vector<GraphEdge> &edges)
{
  vector<DFSStep> steps;
  vector<bool> visited(n, false);
  function<void(int)> rec = [&](int node) {
    visited[node] = true;
    steps.push_back({node, -1, false, false});
    for (int nb : adj[node]) {
      int ei = GFindEdge(edges, node, nb);
      if (!visited[nb]) { steps.push_back({nb, ei, true, false}); rec(nb); }
      else               { steps.push_back({nb, ei, false, false}); }
    }
    steps.push_back({node, -1, false, true});
  };
  rec(start);
  return steps;
}

static void GResetDFS(GraphState &g, Color defaultColor) {
  g.dfsStepIdx = -1; g.dfsTimer = 0.f; g.dfsPaused = false; g.visitOrder = "";
  g.dfsVisited.assign(g.nodes.size(), false);
  g.nodeColors.assign(g.nodes.size(), defaultColor);
  for (auto &e : g.edges) { e.active = false; e.isTree = false; }
}

static void GInitExample(GraphState &g, Color defaultColor) {
  g.nodes = {
    {{560,430},"1"}, {{420,330},"2"}, {{560,230},"3"},
    {{420,130},"4"}, {{700,230},"5"},
  };
  g.edges = {
    {0,1,false,false},{0,2,false,false},{0,4,false,false},
    {1,2,false,false},{1,3,false,false},{2,3,false,false},{2,4,false,false},
  };
  GResetDFS(g, defaultColor);
}

static void GUpdate(GraphState &g, Vector2 mouse, float dt,
                    Rectangle canvas, Color colVisited, Color colCurrent, Color defColor)
{
  if (g.mode == GMODE_RUN_DFS) {
    if (!g.dfsPaused && g.dfsStepIdx < (int)g.dfsSteps.size() - 1) {
      g.dfsTimer += dt;
      if (g.dfsTimer >= 0.55f) {
        g.dfsTimer = 0.f; g.dfsStepIdx++;
        auto &s = g.dfsSteps[g.dfsStepIdx];
        if (!s.backtrack) {
          if (s.edgeIdx >= 0) { g.edges[s.edgeIdx].active = true; g.edges[s.edgeIdx].isTree = s.isTree; }
          if (!g.dfsVisited[s.node]) {
            g.dfsVisited[s.node] = true;
            if (!g.visitOrder.empty()) g.visitOrder += " > ";
            g.visitOrder += g.nodes[s.node].label;
          }
          for (int i = 0; i < (int)g.nodes.size(); i++)
            if (g.dfsVisited[i]) g.nodeColors[i] = colVisited;
          g.nodeColors[s.node] = (s.edgeIdx < 0 || s.isTree) ? colCurrent : colVisited;
        } else {
          if (g.dfsVisited[s.node]) g.nodeColors[s.node] = colVisited;
        }
      }
    }
    if (IsKeyPressed(KEY_SPACE)) g.dfsPaused = !g.dfsPaused;
    if (IsKeyPressed(KEY_R)) {
      GResetDFS(g, defColor);
      auto adj = GBuildAdj((int)g.nodes.size(), g.edges);
      g.dfsSteps = GGenDFS(g.dfsStart, (int)g.nodes.size(), adj, g.edges);
    }
    return;
  }

  if (g.dragging) {
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && g.selectedNode >= 0)
      g.nodes[g.selectedNode].pos = {mouse.x - g.dragOffset.x, mouse.y - g.dragOffset.y};
    else g.dragging = false;
    return;
  }

  if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) return;
  bool inCanvas = CheckCollisionPointRec(mouse, canvas);
  int hit = GNodeAt(g.nodes, mouse);

  if (g.mode == GMODE_ADD_NODE) {
    if (inCanvas) {
      g.nodes.push_back({mouse, to_string((int)g.nodes.size() + 1)});
      GResetDFS(g, defColor);
    }
  } else if (g.mode == GMODE_ADD_EDGE_A) {
    if (hit >= 0) { g.edgeStartA = hit; g.mode = GMODE_ADD_EDGE_B; }
  } else if (g.mode == GMODE_ADD_EDGE_B) {
    if (hit >= 0 && hit != g.edgeStartA && GFindEdge(g.edges, g.edgeStartA, hit) < 0) {
      g.edges.push_back({g.edgeStartA, hit, false, false});
      GResetDFS(g, defColor);
    }
    g.mode = GMODE_ADD_EDGE_A; g.edgeStartA = -1;
  } else if (g.mode == GMODE_REMOVE) {
    if (hit >= 0) {
      g.edges.erase(remove_if(g.edges.begin(), g.edges.end(),
        [hit](const GraphEdge &e){ return e.a==hit || e.b==hit; }), g.edges.end());
      for (auto &e : g.edges) { if (e.a>hit) e.a--; if (e.b>hit) e.b--; }
      g.nodes.erase(g.nodes.begin() + hit);
      for (int i = 0; i < (int)g.nodes.size(); i++) g.nodes[i].label = to_string(i+1);
      if (g.dfsStart >= (int)g.nodes.size()) g.dfsStart = max(0,(int)g.nodes.size()-1);
      g.selectedNode = -1; GResetDFS(g, defColor);
    } else if (inCanvas) {
      for (int i = 0; i < (int)g.edges.size(); i++) {
        Vector2 a = g.nodes[g.edges[i].a].pos, b = g.nodes[g.edges[i].b].pos;
        float dx=b.x-a.x, dy=b.y-a.y, len2=dx*dx+dy*dy;
        float t = len2>0 ? ((mouse.x-a.x)*dx+(mouse.y-a.y)*dy)/len2 : 0;
        t = max(0.f,min(1.f,t));
        float ex=a.x+t*dx-mouse.x, ey=a.y+t*dy-mouse.y;
        if (sqrtf(ex*ex+ey*ey) < 8.f) { g.edges.erase(g.edges.begin()+i); GResetDFS(g,defColor); break; }
      }
    }
  } else {
    if (hit >= 0) { g.selectedNode=hit; g.dragOffset={mouse.x-g.nodes[hit].pos.x,mouse.y-g.nodes[hit].pos.y}; g.dragging=true; }
    else g.selectedNode=-1;
  }
}

static void GDraw(const GraphState &g, Vector2 mouse,
                  Color colEdge, Color colTree, Color colBack,
                  Color colNode, Color colSelected, Color colLabel)
{
  const float R = 18.f;
  for (int i = 0; i < (int)g.edges.size(); i++) {
    Vector2 a=g.nodes[g.edges[i].a].pos, b=g.nodes[g.edges[i].b].pos;
    Color c=colEdge; float t=2.f;
    if (g.edges[i].active) {
      c = g.edges[i].isTree ? colTree : colBack; t=3.f;
      if (!g.edges[i].isTree) {
        float dx=b.x-a.x,dy=b.y-a.y,len=sqrtf(dx*dx+dy*dy);
        int segs=max(1,(int)(len/12));
        for (int s=0;s<segs;s++) if(s%2==0) {
          float t0=(float)s/segs,t1=(float)(s+1)/segs;
          DrawLineEx({a.x+dx*t0,a.y+dy*t0},{a.x+dx*t1,a.y+dy*t1},t,c);
        }
        continue;
      }
    }
    DrawLineEx(a, b, t, c);
  }
  if (g.mode==GMODE_ADD_EDGE_B && g.edgeStartA>=0)
    DrawLineEx(g.nodes[g.edgeStartA].pos, mouse, 1.5f, {200,200,100,140});

  for (int i=0; i<(int)g.nodes.size(); i++) {
    Vector2 p=g.nodes[i].pos;
    Color fill=(g.mode==GMODE_RUN_DFS)?g.nodeColors[i]:colNode;
    if (i==g.selectedNode   && g.mode==GMODE_IDLE)       fill=colSelected;
    if (i==g.edgeStartA     && g.mode==GMODE_ADD_EDGE_B)  fill=colSelected;
    DrawCircleV(p, R, fill);
    DrawCircleLines((int)p.x,(int)p.y,(int)R,{200,220,255,160});
    int tw=MeasureText(g.nodes[i].label.c_str(),16);
    DrawText(g.nodes[i].label.c_str(),(int)(p.x-tw/2),(int)(p.y-8),16,colLabel);
  }
}
