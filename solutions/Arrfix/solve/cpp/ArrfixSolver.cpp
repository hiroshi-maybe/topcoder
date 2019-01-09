#include <fstream>
#include <topcoder>
#include "Arrfix.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
  try {
    std::ifstream ifs(argv[1]);
    vector<int> A; tc::read(ifs, A); tc::next(ifs);
    vector<int> B; tc::read(ifs, B); tc::next(ifs);
    vector<int> F; tc::read(ifs, F);
    ifs.close();

    std::ofstream ofs(argv[2]);
    Arrfix solver;
    tc::show(ofs, solver.mindiff(A, B, F));
    ofs.close();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
