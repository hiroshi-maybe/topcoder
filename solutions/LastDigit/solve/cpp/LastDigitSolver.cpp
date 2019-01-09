#include <fstream>
#include <topcoder>
#include "LastDigit.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
  try {
    std::ifstream ifs(argv[1]);
    int64 S; tc::read(ifs, S);
    ifs.close();

    std::ofstream ofs(argv[2]);
    LastDigit solver;
    tc::show(ofs, solver.findX(S));
    ofs.close();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
