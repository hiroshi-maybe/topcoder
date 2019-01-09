#include <fstream>
#include <topcoder>
#include "UpDownHiking.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
  try {
    std::ifstream ifs(argv[1]);
    int N; tc::read(ifs, N); tc::next(ifs);
    int A; tc::read(ifs, A); tc::next(ifs);
    int B; tc::read(ifs, B);
    ifs.close();

    std::ofstream ofs(argv[2]);
    UpDownHiking solver;
    tc::show(ofs, solver.maxHeight(N, A, B));
    ofs.close();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
