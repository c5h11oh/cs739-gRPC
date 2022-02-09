#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream file("../../random_files/256K.random", std::ios::binary);
    file.seekg(0, std::ios::end);
    uint64_t filesize = file.tellg();
    file.seekg(0);
    std::cout << "filesize=" << filesize << std::endl;
    uint64_t bufsize = 61440; // 60KB
    string buf(bufsize, '\0');

    char pause;
    while (file.read(&buf[0], bufsize)) {
        cout << buf.size() << endl;
    }
    if (file.eof()) {
        buf.resize(file.gcount());
        cout << buf.size() << endl;
    }
}