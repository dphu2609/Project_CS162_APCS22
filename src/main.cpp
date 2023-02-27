#include "../header/function.h"

int main() {
    LinkedList<int> a;
    for (int i = 0; i < 10; i++) {
        a.insertTail(i);
    }
    a.display();
    return 0;
}