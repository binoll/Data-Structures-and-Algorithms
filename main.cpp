#include "data_structures/binary_tree.h"
#include "data_structures/set.h"

int main() {
    BinaryTree<int> tree;


    tree.add(7);

    tree.add(9);

    tree.add(9);

    tree.add(5);

    tree.remove(7);

    return 0;
}
