#include <fstream>
#include <topcoder>
#include "Drbalance.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
    try {
        std::ifstream ifs(argv[1]);
        string s; tc::read(ifs, s); tc::next(ifs);
        int k; tc::read(ifs, k);
        ifs.close();

        std::ofstream ofs(argv[2]);
        Drbalance solver;
        tc::show(ofs, solver.lesscng(s, k));
        ofs.close();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}