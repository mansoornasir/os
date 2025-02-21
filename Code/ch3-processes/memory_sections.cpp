#include <iostream>
#include <cstdlib>

using namespace std;

// Global variable (stored in the Data Segment)
int global_var = 42;

// Static variable (stored in the Data Segment)
static int static_var = 100;

int main() {
    // Local variable (stored in the Stack)
    int local_var = 10;

    // Dynamic memory allocation (stored in the Heap)
    int* heap_var = (int*)malloc(sizeof(int));
    *heap_var = 20;

    // Code (stored in the Text Segment)
    cout << "Addresses of different memory sections:" << endl;
    cout << "Text  Segment (Function) : " << (void*)main << endl;
    cout << "Data  Segment (Global)   : " << &global_var << endl;
    cout << "Data  Segment (Static)   : " << &static_var << endl;
    cout << "Stack Segment (Local)    : " << &local_var << endl;
    cout << "Heap  Segment (Malloc)   : " << heap_var << endl;

    free(heap_var);
    return 0;
}


// size memory_sections -> for sizes of different sections
// text    data     bss     dec     hex filename
// 16752    1552      32   18336    47c0 memory_sections
// Text = Code segment
// Data = Initialized global/static variables
// BSS = Uninitialized global/static variables
