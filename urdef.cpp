#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <fstream>

char toupper_patch(char c) {
    return ('a' <= c && c <= 'z') ? c ^ 0x20 : c;
}

int main(int argc, char **argv) {
   if (argv[1] == NULL) {
      std::cout << "missing argument" << std::endl;
      return 1;
   }
   curlpp::options::Url buffer = curlpp::options::Url(std::string("https://api.urbandictionary.com/v0/define?term=" + std::string(argv[1])));
   std::ofstream output(".tmp.json");
   if (!output) {
      std::cout << "failed to write output file" << std::endl;
      return 1;
   } else {
      output << buffer;
   }
   output.close();
   
   nlohmann::json json;
   std::ifstream input(".tmp.json");
   if (!input) {
      std::cout << "failed to read buffer file" << std::endl;
      return 1;
   } else {
      input >> json;
   }
   input.close();
   
   std::string value = argv[1];
   std::cout << "\033[1;95m\t\t\tꢭ Definitions of " << toupper_patch(argv[1][0]) << value.erase(0, 1) <<  " ꢭ\033[0m\n\n" << std::endl;
   for (auto start = json["list"].begin(); start != json["list"].end(); start++) {
      std::string str = std::string(start.value()["definition"]);
      std::cout << "\033[0;33m•\033[0m " << str << "\n" << std::endl;
   }
   std::remove(".tmp.json");
}
