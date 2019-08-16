#include <iostream>
#include <vector>

using namespace std;

/**
 * Iterator
 * �ṩһ�ַ���˳�����һ���ۺ϶����еĸ���Ԫ�أ����ֲ���¶�ö�����ڲ���ʾ��
 */

// ϡ��ͼ��ʹ���ڽӱ�洢���ݣ�����ͼ
class SparseGraph {
public:
    explicit SparseGraph(int n) {
        // n��ʾͼ�нڵ������
        g = vector<vector<int>>(n);
        this->vertex = n;
    }

    // ��ȡͼ�Ľڵ���
    int getVNumber() const {
        return vertex;
    }

    // ��ͼ�в���һ�������
    void addEdge(int u, int v) {

        g[u].push_back(v);
        g[v].push_back(u);
    }

    // ��ͼ�в���һ�������
    void addEdges(const vector<pair<int, int>>& edges) {

        for (const auto &edge : edges) {
            g[edge.first].push_back(edge.second);
            g[edge.second].push_back(edge.first);
        }
    }

    // ��i���ڵ���ڱߵ�����
    class Iterator {
    public:
        explicit Iterator(const SparseGraph& graph, int i)
            : sparseGraph(graph), index(i), curr(-1) {
        }

        // �Ƿ�����һ�����ڱ�
        bool hasNext() {
            return sparseGraph.g[index].size() > ++curr;
        }

        // ������һ�����ڱ�
        int next() {
            return sparseGraph.g[index][curr];
        }
    private:
        const SparseGraph& sparseGraph;
        // ��i���ڵ�
        int index;
        // ��ǰ���ʵ�λ��
        int curr;
    };

private:
    // �ڽӱ�
    vector<vector<int>> g;
    // �ڵ����
    int vertex;
};

// ����ͼ��ʹ���ڽӾ���洢���ݣ�����ͼ
class DenseGraph {
public:
    explicit DenseGraph(int n) {
        // n��ʾͼ�нڵ������
        g = vector<vector<bool>>(n, vector<bool>(n, false));
        this->vertex = n;
    }

    // ��ȡͼ�Ľڵ���
    int getVNumber() const {
        return vertex;
    }

    // ��ͼ�в���һ�������
    void addEdge(int u, int v) {

        g[u][v] = true;
        g[v][u] = true;
    }

    // ��ͼ�в���һ�������
    void addEdges(const vector<pair<int, int>>& edges) {

        for (const auto &edge : edges) {
            g[edge.first][edge.second] = true;
            g[edge.second][edge.first] = true;
        }
    }

    // ��i���ڵ���ڱߵ�����
    class Iterator {
    public:
        explicit Iterator(const DenseGraph& graph, int i)
                : denseGraph(graph), index(i), curr(-1) {
        }

        // �Ƿ�����һ�����ڱ�
        bool hasNext() {
            // Ѱ����һ���ڽӱߣ�����curr��λ����һ��Ҫ���ʵ�λ��
            while (++curr < denseGraph.vertex)
                if (denseGraph.g[index][curr])
                    return true;
            return false;
        }

        // ������һ�����ڱ�
        int next() {
            return curr;
        }
    private:
        const DenseGraph& denseGraph;
        // ��i���ڵ�
        int index;
        // ��ǰ���ʵ�λ��
        int curr;
    };

private:
    // �ڽӾ���
    vector<vector<bool>> g;
    // �ڵ����
    int vertex;
};

int main() {

    // ʹ���ڽӱ���ڽӾ��󣬶���Ľӿ���һ�µģ��ڲ�ʵ��ϸ�ڶԿͻ�����
    // �������ⲿ͸���ط������а�����Ԫ��
    // ����͸������ҲΪͬһ���㷨�ڶ�����϶����Ͻ��в����ṩ�˿���

    // ����ͼ����4���ڵ㣬5�������
    vector<pair<int, int>> edges = {
            {0, 1}, {0, 2},
            {1, 2}, {1, 3},
            {2, 3}
    };

    // ����һ��ϡ��ͼ��ʹ���ڽӱ�
    SparseGraph sg(4);
    sg.addEdges(edges);

    // ���ϡ��ͼ
    cout << "SparseGraph(Adjacency List)" << endl;
    for (int i = 0; i < sg.getVNumber(); ++i) {

        cout << i << ":";
        SparseGraph::Iterator iter(sg, i);
        while (iter.hasNext())
            cout << " " << iter.next();
        cout << endl;
    }

    // ����һ������ͼ��ʹ���ڽӾ���
    DenseGraph dg(4);
    dg.addEdges(edges);

    // �������ͼ
    cout << "DenseGraph(Adjacency Matrix)" << endl;
    for (int i = 0; i < dg.getVNumber(); ++i) {

        cout << i << ":";
        DenseGraph::Iterator iter(dg, i);
        while (iter.hasNext())
            cout << " " << iter.next();
        cout << endl;
    }

    return 0;
}