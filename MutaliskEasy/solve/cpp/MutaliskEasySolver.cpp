#include <fstream>
#include <topcoder>
#include "MutaliskEasy.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
    try {
        std::ifstream ifs(argv[1]);
        vector<int> x; tc::read(ifs, x);
        ifs.close();

        std::ofstream ofs(argv[2]);
        MutaliskEasy solver;
        tc::show(ofs, solver.minimalAttacks(x));
        ofs.close();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}