#include <fstream>
#include <topcoder>
#include "SetPartialOrder.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
    try {
        std::ifstream ifs(argv[1]);
        vector<int> a; tc::read(ifs, a); tc::next(ifs);
        vector<int> b; tc::read(ifs, b);
        ifs.close();

        std::ofstream ofs(argv[2]);
        SetPartialOrder solver;
        tc::show(ofs, solver.compareSets(a, b));
        ofs.close();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}