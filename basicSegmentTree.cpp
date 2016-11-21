struct BasicSegmentTree {

    struct BasicSegmentTreeValue {
        int value;

        BasicSegmentTreeValue() {

        }

        inline BasicSegmentTreeValue operator+ (const BasicSegmentTreeValue& other) const {
            BasicSegmentTreeValue combinedValue;
            combinedValue.value = value + other.value;
            return combinedValue;
        }
    };

    vector<BasicSegmentTreeValue> nodeData;
    vector<BasicSegmentTreeValue> data;

    void build(int node, int low, int high) {
        if (static_cast<int>(nodeData.size()) <= node) {
            nodeData.resize(static_cast<unsigned int>(node + 1));
        }
        if (low == high) {
            nodeData[node] = data[low];
        } else {
            int middle = (low + high) / 2;
            build(2 * node, low, middle);
            build(2 * node + 1, middle + 1, high);
            nodeData[node] = nodeData[2 * node] + nodeData[2 * node + 1];
        }
    }

    void modifySingleElement(int node, int low, int high, int pos, BasicSegmentTreeValue newValue) {
        if (low == high) {
            nodeData[node] = newValue;
        } else {
            int middle = (low + high) / 2;
            if (pos <= middle) {
                modifySingleElement(2 * node, low, middle, pos, newValue);
            } else {
                modifySingleElement(2 * node + 1, middle + 1, high, pos, newValue);
            }
            nodeData[node] = nodeData[2 * node] + nodeData[2 * node + 1];
        }
    }

    BasicSegmentTreeValue getRangeData(int node, int low, int high, int rangeLow, int rangeHigh) {
        if (low == rangeLow && high == rangeHigh) {
            return nodeData[node];
        } else {
            int middle = (low + high) / 2;
            if (rangeHigh <= middle) {
                return getRangeData(2 * node, low, middle, rangeLow, rangeHigh);
            } else if (rangeLow > middle) {
                return getRangeData(2 * node + 1, middle + 1, high, rangeLow, rangeHigh);
            } else {
                return getRangeData(2 * node, low, middle, rangeLow, middle) + getRangeData(2 * node + 1, middle + 1, high, middle + 1, rangeHigh);
            }
        }
    }

};
