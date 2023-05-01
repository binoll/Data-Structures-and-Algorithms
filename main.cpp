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

    std::cout << tree.findMin();

    tree.remove(7);

    return 0;
}
