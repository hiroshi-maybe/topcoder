#include <fstream>
#include <topcoder>
#include "Initials.cpp"
namespace tc = TopCoder;

int main(int argc, char const *argv[]) {
  try {
    std::ifstream ifs(argv[1]);
    string name; tc::read(ifs, name);
    ifs.close();

    std::ofstream ofs(argv[2]);
    Initials solver;
    tc::show(ofs, solver.getInitials(name));
    ofs.close();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
