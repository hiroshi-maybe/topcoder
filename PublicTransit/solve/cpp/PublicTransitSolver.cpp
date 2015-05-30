#include <fstream>
#include <topcoder>
#include "PublicTransit.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
    try {
        std::ifstream ifs(argv[1]);
        int R; tc::read(ifs, R); tc::next(ifs);
        int C; tc::read(ifs, C);
        ifs.close();

        std::ofstream ofs(argv[2]);
        PublicTransit solver;
        tc::show(ofs, solver.minimumLongestDistance(R, C));
        ofs.close();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}