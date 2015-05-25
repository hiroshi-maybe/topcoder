#include <fstream>
#include <topcoder>
#include "ProblemSetsEasy.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
    try {
        std::ifstream ifs(argv[1]);
        int E; tc::read(ifs, E); tc::next(ifs);
        int EM; tc::read(ifs, EM); tc::next(ifs);
        int M; tc::read(ifs, M); tc::next(ifs);
        int MH; tc::read(ifs, MH); tc::next(ifs);
        int H; tc::read(ifs, H);
        ifs.close();

        std::ofstream ofs(argv[2]);
        ProblemSetsEasy solver;
        tc::show(ofs, solver.maxSets(E, EM, M, MH, H));
        ofs.close();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}