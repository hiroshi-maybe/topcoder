#include <fstream>
#include <topcoder>
#include "TaroFillingAStringDiv1.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
    try {
        std::ifstream ifs(argv[1]);
        int N; tc::read(ifs, N); tc::next(ifs);
        vector<int> position; tc::read(ifs, position); tc::next(ifs);
        string value; tc::read(ifs, value);
        ifs.close();

        std::ofstream ofs(argv[2]);
        TaroFillingAStringDiv1 solver;
        tc::show(ofs, solver.getNumber(N, position, value));
        ofs.close();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}