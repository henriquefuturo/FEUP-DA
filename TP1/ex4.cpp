// By: Gonçalo Leão

#include "exercises.h"

std::vector<int> IntroGraph::topsort() const {
    std::vector<int> res;
    std::stack<int> s;
    if(!isDAG()) {
        return res;
    }

    for (auto& v : getVertexSet()) {
        v->setVisited(false);
    }

    for (auto& v : getVertexSet()) {
        if (!v->isVisited()) {
            topsortDfs(v, s);
        }
    }

    while (!s.empty()) {
        res.push_back(s.top());
        s.pop();
    }

    if (res.size() != getNumVertex()) {
        res.clear();
        return res;
    }

    return res;
}

void IntroGraph::topsortDfs(Vertex *v, std::stack<int> & s) const {
    v->setVisited(true);
    for (auto& e : v->getAdj()) {
        Vertex* vertex = e->getDest();
        if (!vertex->isVisited()) {
            topsortDfs(vertex, s);
        }
    }
    s.push(v->getId());
}

/// TESTS ///
#include <gtest/gtest.h>

void expectTopSort(const IntroGraph graph, std::vector<int> topOrder){
    for(auto u: graph.getVertexSet()) {
        auto itrU = std::find(topOrder.begin(), topOrder.end(), u->getId());
        unsigned int indexU = std::distance(topOrder.begin(), itrU);
        for(auto edge: u->getAdj()) {
            auto v = edge->getDest();
            auto itrV = std::find(topOrder.begin(), topOrder.end(), v->getId());
            unsigned int indexV = std::distance(topOrder.begin(), itrV);
            EXPECT_LT(indexU,indexV);
        }
    }
}

TEST(TP1_Ex4, test_topsort) {
    IntroGraph myGraph;
    myGraph.addVertex(1); myGraph.addVertex(2); myGraph.addVertex(3); myGraph.addVertex(4);
    myGraph.addVertex(5); myGraph.addVertex(6); myGraph.addVertex(7);

    myGraph.addEdge(1, 2, 0);
    myGraph.addEdge(1, 4, 0);
    myGraph.addEdge(1, 3, 0);
    myGraph.addEdge(2, 5, 0);
    myGraph.addEdge(2, 4, 0);
    myGraph.addEdge(3, 6, 0);
    myGraph.addEdge(4, 3, 0);
    myGraph.addEdge(4, 6, 0);
    myGraph.addEdge(4, 7, 0);
    myGraph.addEdge(5, 4, 0);
    myGraph.addEdge(5, 7, 0);
    myGraph.addEdge(7, 6, 0);

    std::vector<int> topOrder = myGraph.topsort();
    EXPECT_EQ(topOrder.size(), 7);
    expectTopSort(myGraph, topOrder); // example of two valid topsorts: "1 2 5 4 3 7 6" and "1 2 5 4 7 3 6"

    // to test including a cycle in the graph
    myGraph.addEdge(3, 1, 0);

    topOrder = myGraph.topsort();
    EXPECT_EQ(topOrder.size(), 0);
}