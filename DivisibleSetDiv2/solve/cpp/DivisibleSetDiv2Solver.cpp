#include <fstream>
#include <topcoder>
#include "DivisibleSetDiv2.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
  try {
    std::ifstream ifs(argv[1]);
    vector<int> b; tc::read(ifs, b);
    ifs.close();

    std::ofstream ofs(argv[2]);
    DivisibleSetDiv2 solver;
    tc::show(ofs, solver.isPossible(b));
    ofs.close();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
