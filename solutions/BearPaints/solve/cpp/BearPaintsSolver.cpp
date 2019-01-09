#include <fstream>
#include <topcoder>
#include "BearPaints.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
    try {
        std::ifstream ifs(argv[1]);
        int W; tc::read(ifs, W); tc::next(ifs);
        int H; tc::read(ifs, H); tc::next(ifs);
        int64 M; tc::read(ifs, M);
        ifs.close();

        std::ofstream ofs(argv[2]);
        BearPaints solver;
        tc::show(ofs, solver.maxArea(W, H, M));
        ofs.close();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}