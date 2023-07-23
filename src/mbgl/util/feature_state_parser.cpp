#include <mbgl/util/feature_state_parser.hpp>

#include <iostream>

namespace mbgl {
namespace util {

FeatureStateParser::~FeatureStateParser() = default;

Value parseObject(const JSValue& object);

Value parseValue(const JSValue& value) {
    switch(value.GetType()){
        case rapidjson::kNullType: {
            return NullValue();
        }
        case rapidjson::kFalseType: {
            return false;
        }
        case rapidjson::kTrueType: {
            return true;
        }
        case rapidjson::kObjectType: {
            return parseObject(value);
        }
        case rapidjson::kArrayType: {
            std::vector<Value> array;
            for (auto a = value.Begin(); a != value.End(); ++a) {
                array.push_back(parseValue(*a));
            }
            return array;
        }
        case rapidjson::kStringType: {
            return std::string(value.GetString(), value.GetStringLength());
        }
        case rapidjson::kNumberType: {
            if(value.IsUint()){ return value.GetUint(); }
            else if(value.IsInt()){ return value.GetInt(); }
            else if(value.IsUint64()){ return value.GetUint64(); }
            else if(value.IsInt64()){ return value.GetInt64(); }
            else {
                return value.GetDouble();
            }
        }
    }
}

Value parseObject(const JSValue& object) {
    FeatureState state;
    for (auto i = object.MemberBegin(); i != object.MemberEnd(); ++i) {
        state[i->name.GetString()] = parseValue(i->value);
    }
    
    return state;
}

FeatureStateParseResult FeatureStateParser::parse(const std::string& json) {
    rapidjson::GenericDocument<rapidjson::UTF8<>, rapidjson::CrtAllocator> document;
    document.Parse<0>(json.c_str());

    if (document.HasParseError()) {
        return std::make_exception_ptr(std::runtime_error(formatJSONParseError(document)));
    }
    
    if (!document.IsObject()) {
        return std::make_exception_ptr(std::runtime_error("feature state must be an object"));
    }
    
    for (auto i = document.MemberBegin(); i != document.MemberEnd(); ++i) {
        state[i->name.GetString()] = parseValue(i->value);
    }
    
    return nullptr;
}



} // namespace utl
} // namespace mbgl
