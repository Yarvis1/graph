#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

int max = 20;
int INF = numeric_limits<int>::max();
int adjMatrix[MAX_VERTICES][MAX_VERTICES];
string vertices[MAX_VERTICES];
int vertexCount = 0;

int getVertexIndex(const string& label);
void addVertex(const string& label);
void addEdge(const string& from, const string& to, int weight);
void removeVertex(const string& label);
void removeEdge(const string& from, const string& to);
void printAdjacencyTable();
void dijkstra(const string& startLabel, const string& endLabel);

int main() {
    for (int i = 0; i < MAX_VERTICES; i++)
        for (int j = 0; j < MAX_VERTICES; j++)
            adjMatrix[i][j] = INF;

    int choice;
    string label1, label2;
    int weight;

    while (true) {
      cout << "0. exit"<<endl;
      cout << "1. add vertex"<<endl;
      cout << "2. add edge"<<endl;
      cout << "3. remove vertex"<<endl;
      cout << "4. remove edge\n"<<endl;
      cout << "5. print adjacency table"<<endl;
      cout << "6. find shortest path"<<endl;
        
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "enter label: ";
                cin >> label1;
                addVertex(label1);
                break;
            case 2:
                cout << "start vert: ";
                cin >> label1;
                cout << "end vert: ";
                cin >> label2;
                cout << "wieght: ";
                cin >> weight;
                addEdge(label1, label2, weight);
                break;
            case 3:
                cout << "enter label: ";
                cin >> label1;
                removeVertex(label1);
                break;
            case 4:
                cout << "start vert: ";
                cin >> label1;
                cout << "end vert: ";
                cin >> label2;
                removeEdge(label1, label2);
                break;
            case 5:
                printAdjacencyTable();
                break;
            case 6:
                cout << "start vert: ";
                cin >> label1;
                cout << "end vertex: ";
                cin >> label2;
                dijkstra(label1, label2);
                break;
            case 0:
                return 0;
            default:
	      cout << "invalid"<<endl;
        }
    }
}

// Function definitions

int getVertexIndex(const string& label) {
    for (int i = 0; i < vertexCount; i++) {
        if (vertices[i] == label)
            return i;
    }
    return -1;
}

void addVertex(const string& label) {
    if (vertexCount >= max) {
      cout << "max vertecies reached"<<endl;
        return;
    }
    if (getVertexIndex(label) != -1) {
      cout << "already exists"<<endl;
        return;
    }
    vertices[vertexCount++] = label;
    cout << "added"<<endl;
}

void addEdge(const string& from, const string& to, int weight) {
    int i = getVertexIndex(from);
    int j = getVertexIndex(to);
    if (i == -1 || j == -1) {
        cout << "not found";
        return;
    }
    adjMatrix[i][j] = weight;
    cout << "added"<<endl;
}

void removeVertex(const string& label) {
    int index = getVertexIndex(label);
    if (index == -1) {
      cout << "not found"<<endl;
        return;
    }

    for (int i = index; i < vertexCount - 1; i++) {
        vertices[i] = vertices[i + 1];
        for (int j = 0; j < vertexCount; j++) {
            adjMatrix[i][j] = adjMatrix[i + 1][j];
            adjMatrix[j][i] = adjMatrix[j][i + 1];
        }
    }
    vertexCount--;
    cout << "removed"<<endl;
}

void removeEdge(const string& from, const string& to) {
    int i = getVertexIndex(from);
    int j = getVertexIndex(to);
    if (i == -1 || j == -1) {
      cout << "not found"<<endl;
        return;
    }
    adjMatrix[i][j] = INF;
    cout << "removed"<<endl;
}

void printAdjacencyTable() {
    cout << setw(10) << " ";
    for (int i = 0; i < vertexCount; i++)
        cout << setw(10) << vertices[i];
    cout << "\n";

    for (int i = 0; i < vertexCount; i++) {
        cout << setw(10) << vertices[i];
        for (int j = 0; j < vertexCount; j++) {
            if (adjMatrix[i][j] == INF)
                cout << setw(10) << "INF";
            else
                cout << setw(10) << adjMatrix[i][j];
        }
        cout << "\n";
    }
}

void dijkstra(const string& startLabel, const string& endLabel) {
    int start = getVertexIndex(startLabel);
    int end = getVertexIndex(endLabel);
    if (start == -1 || end == -1) {
      cout << "not found"<<endl;
        return;
    }

    vector<int> dist(vertexCount, INF);
    vector<bool> visited(vertexCount, false);
    vector<int> prev(vertexCount, -1);

    dist[start] = 0;

    for (int i = 0; i < vertexCount; i++) {
        int u = -1;
        for (int j = 0; j < vertexCount; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u]))
                u = j;
        }

        if (dist[u] == INF) break;
        visited[u] = true;

        for (int v = 0; v < vertexCount; v++) {
            if (adjMatrix[u][v] != INF && dist[u] + adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjMatrix[u][v];
                prev[v] = u;
            }
        }
    }

    if (dist[end] == INF) {
      cout << "no possible path"<<endl;
        return;
    }

    vector<string> path;
    for (int at = end; at != -1; at = prev[at])
        path.insert(path.begin(), vertices[at]);

    cout << "shortest path: ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i != path.size() - 1)
	  cout << " -> ";
    }
    cout << "\nweight: " << dist[end] <<endl;
}
