#include <fstream>
#include <topcoder>
#include "LiveConcert.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
    try {
        std::ifstream ifs(argv[1]);
        vector<int> h; tc::read(ifs, h); tc::next(ifs);
        vector<string> s; tc::read(ifs, s);
        ifs.close();

        std::ofstream ofs(argv[2]);
        LiveConcert solver;
        tc::show(ofs, solver.maxHappiness(h, s));
        ofs.close();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}