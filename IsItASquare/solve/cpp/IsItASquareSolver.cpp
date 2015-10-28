#include <fstream>
#include <topcoder>
#include "IsItASquare.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
    try {
        std::ifstream ifs(argv[1]);
        vector<int> x; tc::read(ifs, x); tc::next(ifs);
        vector<int> y; tc::read(ifs, y);
        ifs.close();

        std::ofstream ofs(argv[2]);
        IsItASquare solver;
        tc::show(ofs, solver.isSquare(x, y));
        ofs.close();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}