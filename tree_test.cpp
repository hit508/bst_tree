#include <stdio.h>
#include <vector>
#include "bst_tree.hpp"


int main(int argc, char** argv)
{
    // vector<int> data = { 45, 24, 53, 12, 37, 93 };
    std::vector<int> data = { 8,2,9,1,5,4,6, 23, 51, 1, 3, 45, 27, 33, 47,12 };

    bst_tree<int, int> bst_tree_instance(data, data);
    printf("====middle order：\n");
    bst_tree_instance.mid_visit();

    printf("====insert middle order：\n");
    bst_tree_instance.instert(-10, -10);
    bst_tree_instance.mid_visit();

    printf("====remove middle order：\n");
    bst_tree_instance.remove(8);
    bst_tree_instance.mid_visit();

    return 0;
}