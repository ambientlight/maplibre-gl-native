#pragma once

#include <mbgl/util/feature.hpp>
#include <mbgl/style/conversion.hpp>
#include <mbgl/util/optional.hpp>

namespace mbgl {
namespace style {
namespace conversion {

template <>
struct Converter<FeatureState> {
public:
    optional<FeatureState> operator()(const Convertible& value, Error& error) const;
};

} // namespace conversion
} // namespace style
} // namespace mbgl
