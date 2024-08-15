#include <iostream>
#include <redirect/api.h>
using namespace redirect;
void print() {
    std::cout << "Print " << '\n';
}

void hookFunctionPrint() {
    std::cout << "Target Var " << '\n';
}
int main() {
    print();

    RelocatableImpl hook;
    hook.install(print, hookFunctionPrint);

    print();

    return {};
}
