#include <fstream>
#include <topcoder>
#include "SubtreeSum.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
  try {
    std::ifstream ifs(argv[1]);
    vector<int> p; tc::read(ifs, p); tc::next(ifs);
    vector<int> x; tc::read(ifs, x);
    ifs.close();

    std::ofstream ofs(argv[2]);
    SubtreeSum solver;
    tc::show(ofs, solver.getSum(p, x));
    ofs.close();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
