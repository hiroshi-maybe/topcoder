#include <fstream>
#include <topcoder>
#include "Hexspeak.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
    try {
        std::ifstream ifs(argv[1]);
        int64 ciphertext; tc::read(ifs, ciphertext);
        ifs.close();

        std::ofstream ofs(argv[2]);
        Hexspeak solver;
        tc::show(ofs, solver.decode(ciphertext));
        ofs.close();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}