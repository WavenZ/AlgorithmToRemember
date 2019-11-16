#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

class Floyd {
public:
	explicit Floyd(vector<vector<int>> map, int n) {
		// Initialize matrix d and matrix p with value that is large enough
		d = vector<vector<int>>(n, vector<int>(n, 99999));
		p = d;
		for (int i = 0; i < n; ++i) d[i][i] = 0;
		for (const auto& path : map) {
			d[path[0]][path[1]] = d[path[1]][path[0]] = path[2];
		}
	}
	void shortest_paths() {
		// Floyd algorithm main process
		int n = d.size();
		for (int k = 0; k < n; ++k)
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					if (d[i][k] + d[k][j] < d[i][j]) {
						d[i][j] = d[i][k] + d[k][j];
						p[i][j] = p[j][i] = k;
					}
	}
	void dfs(int start, int end, vector<int>& path) {
		// In order traverse
		if (p[start][end] == 99999) return;
		dfs(start, p[start][end], path);
		path.push_back(p[start][end]);
		dfs(p[start][end], end, path);
	}
	void print_path(int start, int end){
		// print shortest path for giving start and end
		vector<int> path;
		dfs(start, end, path);
		cout << start << " ";
		for (const auto& p : path)
			cout << p << " ";
		cout << end << endl;
	}
	void print_pd() {
		// print matrix p and matrix d
		for (int i = 0; i < p.size(); ++i) {
			for (int j = 0; j < p.size(); ++j)
				cout << p[i][j] << "\t";
			cout << endl;
		}
		cout << endl;
		for (int i = 0; i < d.size(); ++i) {
			for (int j = 0; j < d.size(); ++j)
				cout << d[i][j] << "\t";
			cout << endl;
		}
	}
private:
	vector<vector<int>> d, p;
};


int main(void) {
	vector<vector<int>> map = {
		{0, 1, 12}, {0, 5, 16}, {0, 6, 14}, {1, 2, 10}, {1, 5, 7}, 
		{6, 4, 8},  {6, 5, 9},  {5, 2, 6},  {5, 4, 2},  {2, 4, 5}, 
	    {2, 3, 3},  {3, 4, 4}
	};
	Floyd F(map, 7);
	F.shortest_paths();
	//F.print_pd();
	F.print_path(0, 3);
	return 0;
}
