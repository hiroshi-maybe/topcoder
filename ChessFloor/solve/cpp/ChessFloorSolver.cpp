#include <fstream>
#include <topcoder>
#include "ChessFloor.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
    try {
        std::ifstream ifs(argv[1]);
        vector<string> floor; tc::read(ifs, floor);
        ifs.close();

        std::ofstream ofs(argv[2]);
        ChessFloor solver;
        tc::show(ofs, solver.minimumChanges(floor));
        ofs.close();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}