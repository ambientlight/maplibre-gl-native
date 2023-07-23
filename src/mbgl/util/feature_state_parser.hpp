#pragma once

#include <mbgl/util/rapidjson.hpp>
#include <mbgl/util/feature.hpp>

namespace mbgl {
namespace util {

using FeatureStateParseResult = std::exception_ptr;

class FeatureStateParser {
public:
    ~FeatureStateParser();
    
    FeatureStateParseResult parse(const std::string&);
    FeatureState state;
};

} // namespace utl
} // namespace mbgl
