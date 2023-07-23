#pragma once

#include <mbgl/style/conversion_impl.hpp>
#include <mbgl/style/conversion.hpp>
#include <string>

namespace mbgl {
namespace style {
namespace conversion {

std::string getJSONType(const Convertible& value);

template <class T, class...Args>
T convertJSONUnsafe(const std::string& json, Error& error, Args&&...args);

} // namespace conversion
} // namespace style
} // namespace mbgl
