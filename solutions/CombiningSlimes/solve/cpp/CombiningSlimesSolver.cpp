#include <fstream>
#include <topcoder>
#include "CombiningSlimes.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
    try {
        std::ifstream ifs(argv[1]);
        vector<int> a; tc::read(ifs, a);
        ifs.close();

        std::ofstream ofs(argv[2]);
        CombiningSlimes solver;
        tc::show(ofs, solver.maxMascots(a));
        ofs.close();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}