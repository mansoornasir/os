#include <iostream>
#include <fstream>
#include <thread>
#include <vector>

using namespace std;

void compressChunk(const string& filename, int chunkID) {
    ifstream input(filename);
    ofstream output("compressed_" + to_string(chunkID) + ".txt");
    string line;

    while (getline(input, line)) {
        output << line[0];  // Dummy compression (keep first char)
    }
}

int main() {
    vector<thread> threads;

    for (int i = 0; i < 4; i++)  // 4 chunks
        threads.emplace_back(compressChunk, "input.txt", i);

    for (auto& t : threads)
        t.join();

    cout << "File compressed in parallel!" << endl;
    return 0;
}
