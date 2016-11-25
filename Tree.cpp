// NOT TESTED YET

struct Tree {

	int LOG_N = 20;

	struct Edge {
		int to;
		long long weight;

		Edge() {

		}

		Edge(int toValue): to(toValue), weight(0) {

		}

		Edge(int toValue, long long weightValue): to(toValue), weight(weightValue) {

		}
	};

	int n, root, timer;
	vector<vector<Edge>> edges;
	vector<long long> depth;
	vector<int> timeIn;
	vector<int> timeOut;
	vector<int> eulerOrdering;
	vector<int> positionInEulerOrdering;
	vector<int> subtreeSize;
	vector<int> verticesSortedByDepth;
	vector<vector<int>> binaryJump;
	vector<char> edgeToParentIsHeavy;

	void readData(bool oriented, bool weighed, bool alreadyZeroIndexed) {
		cin >> n;
		edges.resize(static_cast<unsigned int>(n) + 2);
		depth.resize(static_cast<unsigned int>(n) + 2);
		timeIn.resize(static_cast<unsigned int>(n) + 2);
		timeOut.resize(static_cast<unsigned int>(n) + 2);
		eulerOrdering.resize(static_cast<unsigned int>(n) + 2);
		positionInEulerOrdering.resize(static_cast<unsigned int>(n) + 2);
		subtreeSize.resize(static_cast<unsigned int>(n) + 2);
		verticesSortedByDepth.resize(static_cast<unsigned int>(n) + 2);
		binaryJump.resize(static_cast<unsigned int>(LOG_N));
		for (auto &binaryJumpVectorLayer : binaryJump) {
			binaryJumpVectorLayer.resize(static_cast<unsigned int>(n) + 2);
		}
		edgeToParentIsHeavy.resize(static_cast<unsigned int>(n) + 2);
		for (int i = 0; i < n - 1; i++) {
			int u, v, w;
			cin >> u >> v;
			if (!alreadyZeroIndexed) {
				u--;
				v--;
			}
			if (weighed) {
				cin >> w;
			}
			weighed ? edges[u].emplace_back(Edge(v, w)) : edges[u].emplace_back(Edge(v));
			if (!oriented) {
				weighed ? edges[v].emplace_back(Edge(u, w)) : edges[v].emplace_back(Edge(u));
			}
		}
		root = 0;
	}

	void provideParsedEdgeData(vector<vector<Edge>> &providedEdges) {
		n = static_cast<int>(providedEdges.size());
		edges = providedEdges;
		edges.push_back(vector<Edge>());
		edges.push_back(vector<Edge>());
		depth.resize(static_cast<unsigned int>(n) + 2);
		timeIn.resize(static_cast<unsigned int>(n) + 2);
		timeOut.resize(static_cast<unsigned int>(n) + 2);
		eulerOrdering.resize(static_cast<unsigned int>(n) + 2);
		positionInEulerOrdering.resize(static_cast<unsigned int>(n) + 2);
		subtreeSize.resize(static_cast<unsigned int>(n) + 2);
		verticesSortedByDepth.resize(static_cast<unsigned int>(n) + 2);
		binaryJump.resize(static_cast<unsigned int>(LOG_N));
		for (auto &binaryJumpVectorLayer : binaryJump) {
			binaryJumpVectorLayer.resize(static_cast<unsigned int>(n) + 2);
		}
		edgeToParentIsHeavy.resize(static_cast<unsigned int>(n) + 2);
	}

	void dfs(int currentVertex, int parentVertex, long long currentDepth) {
		eulerOrdering.emplace_back(currentVertex);
		positionInEulerOrdering[currentVertex] = static_cast<int>(eulerOrdering.size()) - 1;
		timeIn[currentVertex] = ++timer;
		depth[currentVertex] = currentDepth;
		subtreeSize[currentVertex] = 1;
		verticesSortedByDepth.emplace_back(currentVertex);
		binaryJump[0][currentVertex] = parentVertex;
		for (int i = 1; i < LOG_N; i++) {
			binaryJump[i][currentVertex] = binaryJump[i - 1][binaryJump[i - 1][currentVertex]];
		}
		for (auto edge : edges[currentVertex]) {
			if (edge.to == parentVertex) {
				continue;
			}
			dfs(edge.to, currentVertex, currentDepth + edge.weight);
			subtreeSize[currentVertex] += subtreeSize[edge.to];
		}
		for (auto edge : edges[currentVertex]) {
			if (edge.to == parentVertex) {
				continue;
			}
			if (2 * subtreeSize[edge.to] > subtreeSize[currentVertex]) {
				edgeToParentIsHeavy[edge.to] = true;
			}
		}
		timeOut[currentVertex] = ++timer;
	}

	void gatherInformation() {
		timer = 0;
		dfs(root, root, 0);
	}

	vector<int> inWhichChain;
	vector<int> positionInChain;
	vector<vector<int>> decomposeToChains() {
		inWhichChain.resize(static_cast<unsigned int>(n) + 2);
		positionInChain.resize(static_cast<unsigned int>(n) + 2);
		sort(verticesSortedByDepth.begin(), verticesSortedByDepth.end(), [&](const int &lhs, const int &rhs) {
			return depth[lhs] < depth[rhs];
		});
		vector<char> assigned(static_cast<unsigned int>(n));
		vector<vector<int>> chains;
		while (!verticesSortedByDepth.empty()) {
			int currentVertex = verticesSortedByDepth.back();
			verticesSortedByDepth.pop_back();
			if (assigned[currentVertex]) {
				break;
			}
			vector<int> newChain;
			while (true) {
				assigned[currentVertex] = true;
				newChain.emplace_back(currentVertex);
				if (!edgeToParentIsHeavy[currentVertex]) {
					break;
				}
				if (currentVertex == root) {
					break;
				}
				currentVertex = binaryJump[0][currentVertex];
			}
			reverse(newChain.begin(), newChain.end());
			chains.emplace_back(newChain);
		}
		for (int i = 0; i < static_cast<int>(chains.size()); i++) {
			for (int j = 0; j < static_cast<int>(chains[i].size()); j++) {
				inWhichChain[chains[i][j]] = i;
				positionInChain[chains[i][j]] = j;
			}
		}
		return chains;
	}

	Tree() {

	}

};
