// DisjointSet.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

class IUnionFind {
public:
    /// declare this method as pure virtual so that it shall be override
    virtual void unionSet(int v1, int v2) = 0;

    /// declare this method as final so that it can't be override
    virtual bool connected(int v1, int v2) final {
        return find(v1) == find(v2);
    }

private:
    /// declare this method as pure virtual so that it shall be override

    virtual int find(int v1) = 0;
};

class UnionQuickFind : public IUnionFind {
public:

    UnionQuickFind(int size) : vertices(size) {
        /// init root as itself
        for (std::size_t i = 0; i < vertices.size(); i++) {
            vertices[i] = static_cast<int>(i);
        }
    }

    /// make v1 and v2's root parent the same
    virtual void unionSet(int v1, int v2) override {
        int r1 = find(v1);
        int r2 = find(v2);
        if (r1 != r2) {
            // update all the vertex's root
            for (auto& vertex : vertices)
                if (vertex == r2)
                    vertex = r1;
        }
    }

private:
    /// find the root parent of v
    virtual int find(int v) override {
        return vertices[v];
    }

    vector<int> vertices;
};

class QuickUnionFind : public IUnionFind {
public:

    QuickUnionFind(int size) : vertices(size) {
        /// init root as itself
        for (std::size_t i = 0; i < vertices.size(); i++) {
            vertices[i] = static_cast<int>(i);
        }
    }

    /// make v1 and v2's root parent the same
    void unionSet(int v1, int v2) {
        int r1 = find(v1);
        int r2 = find(v2);
        if (r1 != r2)
            vertices[r2] = r1;
    }

private:
    /// find the root parent of v
    int find(int v) {
        if (vertices[v] != v)
            return find(vertices[v]);
        return v;
    }

    vector<int> vertices;
};

class UnionFindPathCompression : public IUnionFind {
public:

    UnionFindPathCompression(int size) : vertices(size) {
        /// init root as itself
        for (std::size_t i = 0; i < vertices.size(); i++) {
            vertices[i] = static_cast<int>(i);
        }
    }

    /// make v1 and v2's root parent the same
    void unionSet(int v1, int v2) {
        int r1 = find(v1);
        int r2 = find(v2);
        if (r1 != r2)
            vertices[r2] = r1;
    }

private:
    /// find the root parent of v
    int find(int v) {
        if (vertices[v] != v)
            return vertices[v] = find(vertices[v]);
        return v;
    }
    vector<int> vertices;
};

class UnionFindByRank : public IUnionFind {
public:

    UnionFindByRank(int size) : vertices(size), ranks(size, 1) {
        /// init root as itself
        for (std::size_t i = 0; i < vertices.size(); i++) {
            vertices[i] = static_cast<int>(i);
        }
    }

    /// make v1 and v2's root parent the same
    void unionSet(int v1, int v2) {
        int r1 = find(v1);
        int r2 = find(v2);
        if (r1 != r2) {
            if (ranks[r1] > ranks[r2]) {
                vertices[r2] = r1;
                ranks[r2] = ranks[r1];
            }
            else if (ranks[r1] < ranks[r2]) {
                vertices[r1] = r2;
                ranks[r1] = ranks[r2];
            }
            else {
                vertices[r1] = r2;
                ranks[r1]++;
                ranks[r2]++;
            }
        }
    }

private:
    /// find the root parent of v
    int find(int v) {
        if (vertices[v] != v)
            return vertices[v] = find(vertices[v]);
        return v;
    }
    vector<int> vertices;
    vector<int> ranks;
};


int main()
{
    // for displaying booleans as literal strings, instead of 0 and 1
    cout << boolalpha;

    vector<IUnionFind*> vec = {
        new UnionQuickFind(10),
        new QuickUnionFind(10),
        new UnionFindPathCompression(10),
        new UnionFindByRank(10),
    };

    for (auto puf : vec) {
        // 1-2-5-6-7 3-8-9 4
        puf->unionSet(1, 2);
        puf->unionSet(2, 5);
        puf->unionSet(5, 6);
        puf->unionSet(6, 7);
        puf->unionSet(3, 7);
        puf->unionSet(3, 8);
        puf->unionSet(8, 9); 
        assert(puf->connected(1, 5));
        assert(puf->connected(5, 7));
        assert(puf->connected(3, 7));
        assert(!puf->connected(4, 9));
        // 1-2-5-6-7 3-8-9-4
        puf->unionSet(9, 4);
        assert(puf->connected(4, 9));

        delete puf;
    }

    return 0;
}

