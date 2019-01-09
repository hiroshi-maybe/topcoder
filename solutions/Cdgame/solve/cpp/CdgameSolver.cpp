#include <fstream>
#include <topcoder>
#include "Cdgame.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
    try {
        std::ifstream ifs(argv[1]);
        vector<int> a; tc::read(ifs, a); tc::next(ifs);
        vector<int> b; tc::read(ifs, b);
        ifs.close();

        std::ofstream ofs(argv[2]);
        Cdgame solver;
        tc::show(ofs, solver.rescount(a, b));
        ofs.close();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}