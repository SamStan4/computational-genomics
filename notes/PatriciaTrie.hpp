#ifndef _PATRICIA_TRIE_HPP
#define _PATRICIA_TRIE_HPP

#include "./imports.hpp"

namespace pt {
    class PatriciaTrie {
        public:
            PatriciaTrie() {
                std::cout << "inside of void constructor" << std::endl;
            }
            PatriciaTrie(const std::vector<std::string>& strings) {
                std::cout << "inside of vector<string> constructor" << std::endl;
            }
        private:
    };
}

#endif