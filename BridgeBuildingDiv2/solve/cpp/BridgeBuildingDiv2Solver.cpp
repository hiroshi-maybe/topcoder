#include <fstream>
#include <topcoder>
#include "BridgeBuildingDiv2.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
    try {
        std::ifstream ifs(argv[1]);
        vector<int> a; tc::read(ifs, a); tc::next(ifs);
        vector<int> b; tc::read(ifs, b); tc::next(ifs);
        int K; tc::read(ifs, K);
        ifs.close();

        std::ofstream ofs(argv[2]);
        BridgeBuildingDiv2 solver;
        tc::show(ofs, solver.minDiameter(a, b, K));
        ofs.close();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}