#include "data_structures/binary_tree.h"
#include "data_structures/set.h"

int main() {
    BinaryTree<int> tree;

    tree.add(7);

    tree.add(9);

    tree.add(9);

    tree.add(8);

    tree.add(6);

    tree.add(5);

    tree.add(4);

    tree.remove(7);

    tree.remove(9);

    return 0;
}
