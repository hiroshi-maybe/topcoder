#include <fstream>
#include <topcoder>
#include "BearDartsDiv2.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
    try {
        std::ifstream ifs(argv[1]);
        vector<int> w; tc::read(ifs, w);
        ifs.close();

        std::ofstream ofs(argv[2]);
        BearDartsDiv2 solver;
        tc::show(ofs, solver.count(w));
        ofs.close();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}