#include <fstream>
#include <topcoder>
#include "Xylophone.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
  try {
    std::ifstream ifs(argv[1]);
    vector<int> keys; tc::read(ifs, keys);
    ifs.close();

    std::ofstream ofs(argv[2]);
    Xylophone solver;
    tc::show(ofs, solver.countKeys(keys));
    ofs.close();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
