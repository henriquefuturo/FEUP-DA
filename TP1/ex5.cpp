// By: Gonçalo Leão

#include "exercises.h"

bool IntroGraph::isDAG() const {
    for (auto& v : getVertexSet()) {
        v->setVisited(false);
        v->setProcesssing(false);
    }

    for (auto& v : vertexSet) {
        if (!v->isVisited()) {
            if(!dagDfs(v)) {
                return false;
            }
        }
    }
    return true;
}

bool IntroGraph::dagDfs(Vertex *v) const {
    v->setProcesssing(true);
    for (auto& e : v->getAdj()) {
        Vertex* vertex = e->getDest();
        if (vertex->isProcessing()) {
            return false;
        }
        else if (!vertex->isVisited()) {
            if(!dagDfs(vertex)) {
                return false;
            }
        }
    }
    v->setProcesssing(false);
    v->setVisited(true);
    return true;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex5, test_isDAG) {
    IntroGraph myGraph;

    for(unsigned int i = 0; i < 6; i++) {
        myGraph.addVertex(i);
    }

    myGraph.addEdge(1, 2, 0);
    myGraph.addEdge(2, 5, 0);
    myGraph.addEdge(5, 4, 0);
    myGraph.addEdge(3, 1, 0);
    myGraph.addEdge(0, 4, 0);

    EXPECT_EQ(myGraph.isDAG(), true);

    myGraph.addEdge(4, 1, 0);

    EXPECT_EQ(myGraph.isDAG(), false);
}