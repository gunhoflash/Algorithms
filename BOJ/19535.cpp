#include <iostream>
#include <vector>

using namespace std;

struct Vertex {
	int n_adjacents;
	vector<Vertex *> adjacents;
};

int main(void) {
	int
		i, // indexer
		N, // the number of vertices
		u, v,
		n_adjacents;

	long long
		n_D_tree,
		n_G_tree;

	vector<Vertex>
		vertices;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of vertices
	cin >> N;

	// init all vertices
	vertices.resize(N);
	for (i = 0; i < N; i++) {
		vertices[i].n_adjacents = 0;
	}

	// set edges
	for (i = 1; i < N; i++) {
		cin >> u >> v;
		vertices[u - 1].n_adjacents++;
		vertices[v - 1].n_adjacents++;
		vertices[u - 1].adjacents.push_back(&vertices[v - 1]);
		vertices[v - 1].adjacents.push_back(&vertices[u - 1]);
	}

	// count the number of D-tree and G-tree
	n_D_tree = n_G_tree = 0;
	for (i = 0; i < N; i++) {
		n_adjacents = vertices[i].n_adjacents;
		// count D-tree
		for (auto adjacent : vertices[i].adjacents) {
			n_D_tree += (adjacent->n_adjacents - 1) * (n_adjacents - 1);
		}

		// count G-tree
		n_G_tree += ((long long) n_adjacents) * (n_adjacents - 1) * (n_adjacents - 2) / 6;
	}

	// adjust duplicated count
	n_D_tree /= 2;

	// print the answer
	if (n_D_tree > n_G_tree * 3)
		cout << 'D';
	else if (n_D_tree < n_G_tree * 3)
		cout << 'G';
	else
		cout << "DUDUDUNGA";

	return 0;
}
