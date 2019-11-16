#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>
using namespace std;
struct Vertex {
	int d = 99999;
	int id;
	Vertex* p = nullptr;
};
struct Edge {
	Vertex* u = nullptr;
	Vertex* v = nullptr;
	int w;
};
struct Graph {
	vector<Vertex> V;
	vector<Edge> E;
};
class Ford {
public:
	explicit Ford(Graph& G) : G_(G) {};
	void init_single_source(unsigned s) {
		G_.V[s].d = 0;
	}
	void relax(Edge& edge) {
		if (edge.v->d > edge.u->d + edge.w) {
			edge.v->d = edge.u->d + edge.w;
			edge.v->p = edge.u;
		}
	}
	bool bellman_ford(unsigned s) {
		init_single_source(s);
		for (int i = 0; i < G_.V.size() - 1; ++i) {
			for (Edge& edge : G_.E) {
				relax(edge);
			}
		}
		for (const Edge& edge : G_.E) {
			if (edge.v->d > edge.u->d + edge.w)
				return false;
		}
		return true;
	}
	void print_path(unsigned i) {
		Vertex* v = &G_.V[i];
		cout << i << " ";
		while (v->p) {
			cout << v->p->id << " ";
			v = v->p;
		}
		cout << endl;
	}
private:
	Graph& G_;
};

Graph make_graph(vector<vector<pair<int, int>>> vec) {
	Graph G;
	// Load Vertexes
	for (int i = 0; i < vec.size(); ++i) {
		G.V.push_back({ 99999, i, nullptr});
	}
	// Load Edges
	for (int i = 0; i < vec.size(); ++i) {
		Vertex* u = &G.V[i];
		for (int j = 0; j < vec[i].size(); ++j) {
			Vertex* v = &G.V[vec[i][j].first];
			int w = vec[i][j].second;
			G.E.push_back({ u, v, w });
		}
	}
	return G;
}
int main(void) {
	vector<vector<pair<int, int>>> vec = {
		{{1, 5}, {3, 8}, {4, -4}},
		{{0, -2}},
		{{0, 6}, {3, 7}},
		{{1, -3}, {4, 9}},
		{{2, 2}, {1, 7}}
	};
	Graph G = make_graph(vec);
	Ford F(G);
	F.bellman_ford(2);
	for (int i = 0; i < vec.size(); ++i)
		F.print_path(i);
	return 0;
}
