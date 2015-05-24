#include <fstream>
#include <topcoder>
#include "InfiniteString.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
    try {
        std::ifstream ifs(argv[1]);
        string s; tc::read(ifs, s); tc::next(ifs);
        string t; tc::read(ifs, t);
        ifs.close();

        std::ofstream ofs(argv[2]);
        InfiniteString solver;
        tc::show(ofs, solver.equal(s, t));
        ofs.close();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}