#include <fstream>
#include <topcoder>
#include "PartisanGame.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
  try {
    std::ifstream ifs(argv[1]);
    int n; tc::read(ifs, n); tc::next(ifs);
    vector<int> a; tc::read(ifs, a); tc::next(ifs);
    vector<int> b; tc::read(ifs, b);
    ifs.close();

    std::ofstream ofs(argv[2]);
    PartisanGame solver;
    tc::show(ofs, solver.getWinner(n, a, b));
    ofs.close();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
