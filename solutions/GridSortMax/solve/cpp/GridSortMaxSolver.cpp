#include <fstream>
#include <topcoder>
#include "GridSortMax.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
  try {
    std::ifstream ifs(argv[1]);
    int n; tc::read(ifs, n); tc::next(ifs);
    int m; tc::read(ifs, m); tc::next(ifs);
    vector<int> grid; tc::read(ifs, grid);
    ifs.close();

    std::ofstream ofs(argv[2]);
    GridSortMax solver;
    tc::show(ofs, solver.findMax(n, m, grid));
    ofs.close();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
