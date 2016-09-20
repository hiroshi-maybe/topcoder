#include <fstream>
#include <topcoder>
#include "RepeatStringEasy.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
  try {
    std::ifstream ifs(argv[1]);
    string s; tc::read(ifs, s);
    ifs.close();

    std::ofstream ofs(argv[2]);
    RepeatStringEasy solver;
    tc::show(ofs, solver.maximalLength(s));
    ofs.close();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
