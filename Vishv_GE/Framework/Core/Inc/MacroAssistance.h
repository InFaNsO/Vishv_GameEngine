#pragma once


#define ENUM_MACRO(name, ...)\
    enum class name { __VA_ARGS__};\
    const std::string& ToString(name value)\
     {\
        const std::string name##String(#__VA_ARGS__);\
        static std::vector<std::string> name##Strings;\
        if( name##Strings.size() == 0)\
        {\
            std::stringstream ss(name##String);\
            std::string token;\
            while (std::getline(ss, token, ',')) \
            {\
                name##Strings.push_back(token);\
            }\
        }\
        name##Strings[static_cast<int>(value)];\
     }\

