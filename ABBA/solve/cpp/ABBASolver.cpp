#include <fstream>
#include <topcoder>
#include "ABBA.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
    try {
        std::ifstream ifs(argv[1]);
        string initial; tc::read(ifs, initial); tc::next(ifs);
        string target; tc::read(ifs, target);
        ifs.close();

        std::ofstream ofs(argv[2]);
        ABBA solver;
        tc::show(ofs, solver.canObtain(initial, target));
        ofs.close();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}