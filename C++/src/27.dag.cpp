#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>
using namespace std;
struct Vertex {
	Vertex(int vd, int vid, int vdepth, shared_ptr<Vertex> vp):
		d(vd),
		id(vid),
		depth(vdepth),
		p(vp){}
	int d = 99999;
	int id;
	int depth = 0;
	shared_ptr<Vertex> p = nullptr;
};
struct Adj_ {
	shared_ptr<Vertex> u = nullptr;
	vector<shared_ptr<Vertex>> V;
	vector<int> W;
};
struct Graph {
	vector<Adj_> Adj;
};
class DAG {
public:
	explicit DAG(Graph& G) : G_(G) {};
	void init_single_source(unsigned id) {
		for (int i = 0; i < G_.Adj.size(); ++i)
			if (G_.Adj[i].u->id == id)
				G_.Adj[i].u->d = 0;
	}
	void relax(shared_ptr<Vertex> u, shared_ptr<Vertex> v, int w) {
		if (v->d > u->d + w) {
			v->d = u->d + w;
			v->p = u;
		}
	}
	bool shortest_paths(unsigned s) {
		top_sort();
		init_single_source(s);
		for (int i = 0; i < G_.Adj.size() - 1; ++i) {
			for (int j = 0; j < G_.Adj[i].V.size(); ++j) {
					relax(G_.Adj[i].u, G_.Adj[i].V[j],G_.Adj[i].W[j]);
			}
		}
		return true;
	}
	void top_sort() {
		for (auto& adj : G_.Adj) {
			adj.u->depth = dfs(adj.u->id);
		}
		sort(G_.Adj.begin(), G_.Adj.end(), [](const auto& a, const auto& b) { return a.u->depth > b.u->depth; });
	}
	int dfs(unsigned i) {
		if (G_.Adj[i].u->depth != 0) return G_.Adj[i].u->depth;
		int max_len = 1;
		for (int j = 0; j < G_.Adj[i].V.size(); ++j)
			max_len = max(max_len, 1 + dfs(G_.Adj[i].V[j]->id));
		return max_len;
	}
	void print_path(unsigned i) {
		shared_ptr<Vertex> v = G_.Adj[i].u;
		cout << v->id << " ";
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
		shared_ptr<Vertex> u = make_shared<Vertex>(99999, i, 0, nullptr);
		G.Adj.push_back({ u, {}, {} });
	}
	// Load Edges
	for (int i = 0; i < vec.size(); ++i) {
		shared_ptr<Vertex> u = G.Adj[i].u;
		for (int j = 0; j < vec[i].size(); ++j) {
			shared_ptr<Vertex> v = G.Adj[vec[i][j].first].u;
			int w = vec[i][j].second;
			G.Adj[i].V.push_back(v);
			G.Adj[i].W.push_back(w);
		}
	}
	return G;
}
int main(void) {
	vector<vector<pair<int, int>>> vec = {
		{{1, 7}, {2, 4}, {3, 2}},
		{{2, -1}, {3, 1}},
		{{3, -2}},
		{},
		{{5, 5}, {0, 3}},
		{{0, 2}, {1, 6}}
	};
	Graph G = make_graph(vec);
	DAG D(G);
	D.shortest_paths(4);
	for (int i = 0; i < vec.size(); ++i)
		D.print_path(i);
	return 0;
}
