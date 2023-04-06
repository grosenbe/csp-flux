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
    if (line[0] == '#') continue;

    stringstream ss(line);
    std::array<string, 4> tokens;
    for (auto index = 0u; index < 4; ++index) {
      std::getline(ss, tokens[index], '\t');
    }

    heliostats.push_back(std::make_unique<heliostat>(stod(tokens[0]),
                                                     stod(tokens[1]),
                                                     stod(tokens[2]),
                                                     stod(tokens[3])));
  }
}

heliostat &
field::GetHeliostat(size_t heliostatIdx) {
  return *(heliostats[heliostatIdx]);
}
