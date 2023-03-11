// By: Gonçalo Leão

#include "exercises.h"

#include "TestAux.h"

std::vector<std::vector<int>> IntroGraph::computeSCCs() const {
    std::vector<std::vector<int>> sccs;
    std::stack<Vertex*> s;

    for (auto& v : getVertexSet()) {
        v->setVisited(false);
    }

    for (auto& v : getVertexSet()) {
        if (!v->isVisited()) {
            firstKosarajuSharirDFS(v, s);
        }
    }

    for (auto& v : getVertexSet()) {
        v->setVisited(false);
    }

    while (!s.empty()) {
        Vertex* v = s.top();
        s.pop();
        if(!v->isVisited()) {
            std::vector<int> scc;
            secondKosarajuSharirDFS(v, scc);
            sccs.push_back(scc);
        }
    }
    return sccs;
}

void IntroGraph::firstKosarajuSharirDFS(Vertex *v, std::stack<Vertex *> &s) const {
    v->setVisited(true);
    for (auto& e : v->getAdj()) {
        Vertex* vertex = e->getDest();
        if(!vertex->isVisited()) {
            firstKosarajuSharirDFS(vertex, s);
        }
    }
    s.push(v);
}

void IntroGraph::secondKosarajuSharirDFS(Vertex *v, std::vector<int> &res) const {
    v->setVisited(true);
    res.push_back(v->getId());
    for (auto& e : v->getIncoming()) {
        Vertex* vertex = e->getOrig();
        if (!vertex->isVisited()) {
            secondKosarajuSharirDFS(vertex, res);
        }
    }
}

/// TESTS ///
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(TP1_Ex6, test_SCC) {
    IntroGraph graph;
    createNetwork(graph);
    std::vector<std::vector<int>> sccs = graph.computeSCCs();

    EXPECT_EQ(sccs.size(), 3);
    EXPECT_THAT(sccs,  ::testing::UnorderedElementsAre(::testing::UnorderedElementsAre(1,2,3,5,6), ::testing::UnorderedElementsAre(4), ::testing::UnorderedElementsAre(7)));

    IntroGraph graph2;
    for(unsigned int i = 1; i <= 5; i++) {
        graph2.addVertex(i);
    }
    graph2.addEdge(1,3,0);
    graph2.addEdge(1,4,0);
    graph2.addEdge(2,1,0);
    graph2.addEdge(3,2,0);
    graph2.addEdge(4,5,0);
    sccs = graph2.computeSCCs();

    EXPECT_EQ(sccs.size(), 3);
    EXPECT_THAT(sccs,  ::testing::UnorderedElementsAre(::testing::UnorderedElementsAre(1,2,3), ::testing::UnorderedElementsAre(4), ::testing::UnorderedElementsAre(5)));
}