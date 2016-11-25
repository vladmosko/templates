// NOT TESTED YET

namespace myExceptions {

	bool ignoreExceptions = false;

	inline void throwNewException(string msg) {
		if (!ignoreExceptions) {
			printf("RAISED NEW EXCEPTION: ");
			puts(msg.c_str());
		}
	}

};

struct ConvexHullTrickMax {

	double EPS = 1e-9;

	struct Line {
		double k, b;
		int id;

		Line() {

		}

		Line(double kValue, double bValue, int idValue): k(kValue), b(bValue), id(idValue) {

		}

		inline double valueAtPoint(double x) const {
			return k * x + b;
		}

		inline bool operator< (const Line& other) const {
			return k > other.k;
		}
	};

	inline bool badTriple(Line a, Line b, Line c) {
		return (a.k - c.k) * (a.b - b.b) <= (a.b - c.b) * (a.k - b.k);
	}

	vector<Line> convexHull;

	void addLine(Line newLine) {
		if (!convexHull.empty() && fabs(convexHull.back().k - newLine.k) <= EPS && convexHull.back().b > newLine.b) {
			return;
		}
		convexHull.emplace_back(newLine);
		while (true) {
			int hullSize = static_cast<int>(convexHull.size());
			if (hullSize <= 2 || !badTriple(convexHull[hullSize - 2], convexHull[hullSize - 3], convexHull.back())) {
				break;
			}
			Line tmp = convexHull.back();
			convexHull.pop_back();
			convexHull.pop_back();
			convexHull.emplace_back(tmp);
		}
	}

	inline Line findBest(double atPoint) {
		if (convexHull.empty()) {
			myExceptions::throwNewException("Convex hull is empty!");
		}
		Line res;
		double ret = numeric_limits<double>::min();
		int low = 0;
		int high = static_cast<int>(convexHull.size()) - 1;
		for (int iteration = 0; iteration < 20; iteration++) {
			int middle0 = (low + high) / 2;
			double f0 = convexHull[middle0].valueAtPoint(atPoint);
			if (f0 > ret) {
				ret = f0;
				res = convexHull[middle0];
			}
			if (middle0 + 1 < static_cast<int>(convexHull.size())) {
				double f1 = convexHull[middle0 + 1].valueAtPoint(atPoint);
				if (f1 > ret) {
					ret = f1;
					res = convexHull[middle0 + 1];
				}
				if (f1 >= f0) {
					low = middle0 + 1;
				} else {
					high = middle0;
				}
			}
		}
		return res;
	}

};
