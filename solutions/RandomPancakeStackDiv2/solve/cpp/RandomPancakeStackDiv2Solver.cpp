#include <fstream>
#include <topcoder>
#include "RandomPancakeStackDiv2.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
    try {
        std::ifstream ifs(argv[1]);
        vector<int> d; tc::read(ifs, d);
        ifs.close();

        std::ofstream ofs(argv[2]);
        RandomPancakeStackDiv2 solver;
        tc::show(ofs, solver.expectedDeliciousness(d));
        ofs.close();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}