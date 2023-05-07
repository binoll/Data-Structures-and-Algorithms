#include "data_structures/priority_queue.h"
#include "data_structures/set.h"

int main() {
    PriorityQueue<std::string> queue("Dad", 100);

    queue.push("Saveliy", 1);

    queue.push("mama", 1);
    queue.push("Oleg", 4);

    std::cout << queue;
    std::cout << queue.popMin();
    std::cout << queue;
    std::cout << queue.findMax();
    return 0;
}
