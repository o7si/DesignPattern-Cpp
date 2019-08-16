#include <iostream>
#include <vector>

using namespace std;

/**
 * Iterator
 * 提供一种方法顺序访问一个聚合对象中的各个元素，而又不暴露该对象的内部表示。
 */

// 稀疏图：使用邻接表存储数据，无向图
class SparseGraph {
public:
    explicit SparseGraph(int n) {
        // n表示图中节点的数量
        g = vector<vector<int>>(n);
        this->vertex = n;
    }

    // 获取图的节点数
    int getVNumber() const {
        return vertex;
    }

    // 向图中插入一条无向边
    void addEdge(int u, int v) {

        g[u].push_back(v);
        g[v].push_back(u);
    }

    // 向图中插入一组无向边
    void addEdges(const vector<pair<int, int>>& edges) {

        for (const auto &edge : edges) {
            g[edge.first].push_back(edge.second);
            g[edge.second].push_back(edge.first);
        }
    }

    // 第i个节点的邻边迭代器
    class Iterator {
    public:
        explicit Iterator(const SparseGraph& graph, int i)
            : sparseGraph(graph), index(i), curr(-1) {
        }

        // 是否有下一个相邻边
        bool hasNext() {
            return sparseGraph.g[index].size() > ++curr;
        }

        // 返回下一个相邻边
        int next() {
            return sparseGraph.g[index][curr];
        }
    private:
        const SparseGraph& sparseGraph;
        // 第i个节点
        int index;
        // 当前访问的位置
        int curr;
    };

private:
    // 邻接表
    vector<vector<int>> g;
    // 节点个数
    int vertex;
};

// 稠密图：使用邻接矩阵存储数据，无向图
class DenseGraph {
public:
    explicit DenseGraph(int n) {
        // n表示图中节点的数量
        g = vector<vector<bool>>(n, vector<bool>(n, false));
        this->vertex = n;
    }

    // 获取图的节点数
    int getVNumber() const {
        return vertex;
    }

    // 向图中插入一条无向边
    void addEdge(int u, int v) {

        g[u][v] = true;
        g[v][u] = true;
    }

    // 向图中插入一组无向边
    void addEdges(const vector<pair<int, int>>& edges) {

        for (const auto &edge : edges) {
            g[edge.first][edge.second] = true;
            g[edge.second][edge.first] = true;
        }
    }

    // 第i个节点的邻边迭代器
    class Iterator {
    public:
        explicit Iterator(const DenseGraph& graph, int i)
                : denseGraph(graph), index(i), curr(-1) {
        }

        // 是否有下一个相邻边
        bool hasNext() {
            // 寻找下一个邻接边，并将curr定位到下一个要访问的位置
            while (++curr < denseGraph.vertex)
                if (denseGraph.g[index][curr])
                    return true;
            return false;
        }

        // 返回下一个相邻边
        int next() {
            return curr;
        }
    private:
        const DenseGraph& denseGraph;
        // 第i个节点
        int index;
        // 当前访问的位置
        int curr;
    };

private:
    // 邻接矩阵
    vector<vector<bool>> g;
    // 节点个数
    int vertex;
};

int main() {

    // 使用邻接表或邻接矩阵，对外的接口是一致的，内部实现细节对客户隐藏
    // 可以让外部透明地访问其中包含的元素
    // 这种透明遍历也为同一种算法在多个集合对象上进行操作提供了可能

    // 假设图中有4个节点，5条无向边
    vector<pair<int, int>> edges = {
            {0, 1}, {0, 2},
            {1, 2}, {1, 3},
            {2, 3}
    };

    // 生成一个稀疏图（使用邻接表）
    SparseGraph sg(4);
    sg.addEdges(edges);

    // 输出稀疏图
    cout << "SparseGraph(Adjacency List)" << endl;
    for (int i = 0; i < sg.getVNumber(); ++i) {

        cout << i << ":";
        SparseGraph::Iterator iter(sg, i);
        while (iter.hasNext())
            cout << " " << iter.next();
        cout << endl;
    }

    // 生成一个稠密图（使用邻接矩阵）
    DenseGraph dg(4);
    dg.addEdges(edges);

    // 输出稠密图
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