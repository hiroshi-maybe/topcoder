#include <fstream>
#include <topcoder>
#include "XYZCoder.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
  try {
    std::ifstream ifs(argv[1]);
    int room; tc::read(ifs, room); tc::next(ifs);
    int size; tc::read(ifs, size);
    ifs.close();

    std::ofstream ofs(argv[2]);
    XYZCoder solver;
    tc::show(ofs, solver.countWays(room, size));
    ofs.close();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
