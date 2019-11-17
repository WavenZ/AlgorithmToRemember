#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <memory>
#include <unordered_map>

using namespace std;

struct Vertex {
	// Vertex datastruct
	Vertex(int vid, int vd, shared_ptr<Vertex> vp) :
		id(vid), d(vd), p(vp){}
	int id;
	int d;
	shared_ptr<Vertex> p;
};
struct Edge {
	// Edge datastruct
	shared_ptr<Vertex> u;
	shared_ptr<Vertex> v;
	int w;
};
using ADJ = unordered_map<int, vector<Edge>>;
struct Graph {
	// Graph datastruct
	vector<shared_ptr<Vertex>> V;
	ADJ Adj;
};
bool operator<(const shared_ptr<Vertex> a, const shared_ptr<Vertex> b) {
	// Overload the "<" operator for priority_queue
	// To implement the "big-endian" priority_queue, return ">" rather than "<"
	return a->d > b->d;
}
class Dijkstra {
public:
	Dijkstra(Graph& Graph) : G(Graph) {}
	void initialize_single_source(int id) {
		// Initialize single source
		for (int i = 0; i < G.V.size(); ++i)
			if (G.V[i]->id == id)
				G.V[i]->d = 0;
	}
	void relax(priority_queue<shared_ptr<Vertex>>& Q, Edge& edge) {
		// Relaxation operation
		if (edge.v->d > edge.u->d + edge.w) {
			edge.v->d = edge.u->d + edge.w;
			edge.v->p = edge.u;
			Q.push(edge.v);
		}
	}
	void shortest_paths(int id) {
		// Dijkstra algorithm main process
		initialize_single_source(id);
		vector<int> S(G.V.size(), 0);
		priority_queue<shared_ptr<Vertex>> Q;
		Q.push(G.V[id]);
		while (!Q.empty()) {
			shared_ptr<Vertex> u = Q.top(); Q.pop();
			if (S[u->id]) continue;
			S[u->id] = 1;
			for (int i = 0; i < G.Adj[u->id].size(); ++i)
				relax(Q, G.Adj[u->id][i]);
		}
	}
	void print_path(unsigned i) {
		// Print the path backwards
		shared_ptr<Vertex> v = G.V[i];
		cout << v->id;
		while (v->p) {
			cout << " <- ";
			cout << v->p->id;
			v = v->p;
		}
		cout << endl;
	}
private:
	Graph& G;
};
Graph make_graph(const vector<vector<pair<int, int>>>& vec) {
	Graph G;
	// Load vertexes
	for (int i = 0; i < vec.size(); ++i) {
		shared_ptr<Vertex> u = make_shared<Vertex>(i, 99999, nullptr);
		G.V.push_back(u);
		G.Adj[u->id] = {};
	}
	// Load edges
	for (int i = 0; i < vec.size(); ++i) {
		shared_ptr<Vertex> u = G.V[i];
		for (int j = 0; j < vec[i].size(); ++j) {
			shared_ptr<Vertex> v = G.V[vec[i][j].first];
			int w = vec[i][j].second;
			G.Adj[u->id].push_back({ u, v, w });
		}
	}
	return G;
}
int main(void) {
	vector<vector<pair<int, int>>> vec = {
		{{1, 1}, {3, 2}},
		{{4, 4}},
		{{0, 10}, {3, 5}},
		{{0, 2}, {1, 9}, {4, 2}},
		{{1, 6}, {2, 7}} };
	Graph G = make_graph(vec);
	Dijkstra D(G);
	D.shortest_paths(2);
	for (int i = 0; i < G.V.size(); ++i)
		D.print_path(i);
	return 0;
}
