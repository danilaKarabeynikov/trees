#include "pch.h"
#include "../OptimumTree/OptimumTree.h"
#include "../OptimumTree/GraphVizFunctions.h"
#define fileName	"Graph.dot"

TEST(OptimumTreeTests, CorrectSearch) 
{
    int keyCount = 4;
    int k[]{0, 1, 2, 3};
    int p[]{6, 2, 8, 7};
    int pCount = 4;
    int q[]{0, 0, 0, 0, 0};

    OptimumTree<int> tree(k, keyCount, p, pCount, q);
    GraphViz<int> graph(&tree, fileName);
    graph.drawGraph();

    EXPECT_TRUE(tree.searchNode(0));
    EXPECT_TRUE(tree.searchNode(1));
    EXPECT_TRUE(tree.searchNode(2));
    EXPECT_TRUE(tree.searchNode(3));

    EXPECT_FALSE(tree.searchNode(4));
    EXPECT_FALSE(tree.searchNode(-1));
}

TEST(OptimumTreeTests, CorrectTreeToStr)
{
    int keyCount = 4;
    int k[]{ 0, 1, 2, 3 };
    int p[]{ 6, 2, 8, 7 };
    int pCount = 4;
    int q[]{ 3, 4, 1, 5, 8 };

    OptimumTree<int> tree(k, keyCount, p, pCount, q);
    GraphViz<int> graph(&tree, fileName);
    graph.drawGraph();

    tree.printTree();
    EXPECT_STREQ("2013", tree.treeToStr().c_str());
}

TEST(OptimumTreeTests, ChangeTreeWithQArr)
{
    int keyCount = 4;
    int k[]{ 0, 1, 2, 3};
    int p[]{ 6, 2, 8, 7 };
    int pCount = 4;
    int q[]{ 1, 2, 9, 17, 1 };

    OptimumTree<int> tree(k, keyCount, p, pCount, q);
    GraphViz<int> graph(&tree, fileName);
    graph.drawGraph();

    tree.printTree();
    EXPECT_STREQ("2103", tree.treeToStr().c_str());
}
