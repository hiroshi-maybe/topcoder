#include <fstream>
#include <topcoder>
#include "BichromeBoard.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
    try {
        std::ifstream ifs(argv[1]);
        vector<string> board; tc::read(ifs, board);
        ifs.close();

        std::ofstream ofs(argv[2]);
        BichromeBoard solver;
        tc::show(ofs, solver.ableToDraw(board));
        ofs.close();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}