#include <fstream>
#include <topcoder>
#include "TriangleMaking.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
  try {
    std::ifstream ifs(argv[1]);
    int a; tc::read(ifs, a); tc::next(ifs);
    int b; tc::read(ifs, b); tc::next(ifs);
    int c; tc::read(ifs, c);
    ifs.close();

    std::ofstream ofs(argv[2]);
    TriangleMaking solver;
    tc::show(ofs, solver.maxPerimeter(a, b, c));
    ofs.close();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
