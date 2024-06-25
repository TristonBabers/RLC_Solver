#ifndef Delimiter_hpp
#define Delimiter_hpp

#include <string>

namespace RLC_SOLVER {

    static std::string delimiter(const std::string& aStringToDelimit) {
        return "{" + aStringToDelimit + "}";
    }

}

#endif /* Delimiter_hpp */