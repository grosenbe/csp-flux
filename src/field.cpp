#include "field.h"

#include <array>
#include <fstream>
#include <sstream>
#include <string>

#include "heliostat.h"

using std::ifstream;
using std::string;
using std::stringstream;

using namespace cspflux;

field::field(const std::string &path) {
  ifstream ifs(path, std::ifstream::in);
  if (!ifs.good())
    throw std::runtime_error("Error: unable to open input file at " + path);

  std::string line;
  while (std::getline(ifs, line)) {
    stringstream ss(line);
    std::array<string, 3> tokens;
    auto index = 0u;
    while (index < 3) {
      std::getline(ss, tokens[index++], '\t');
    }

    heliostats.push_back(std::make_unique<heliostat>(stod(tokens[0]),
                                                     stod(tokens[1]),
                                                     stod(tokens[2])));
  }
}

heliostat &
field::GetHeliostat(size_t heliostatIdx) {
  return *(heliostats[heliostatIdx]);
}
