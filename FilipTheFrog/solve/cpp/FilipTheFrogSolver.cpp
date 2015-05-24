#include <fstream>
#include <topcoder>
#include "FilipTheFrog.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
    try {
        std::ifstream ifs(argv[1]);
        vector<int> positions; tc::read(ifs, positions); tc::next(ifs);
        int L; tc::read(ifs, L);
        ifs.close();

        std::ofstream ofs(argv[2]);
        FilipTheFrog solver;
        tc::show(ofs, solver.countReachableIslands(positions, L));
        ofs.close();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}