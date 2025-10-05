#pragma once
#include <map>
#include <sstream>
#include <string>

class SimpleJSON {
    std::map<std::string, std::string> data;
public:
    void add(const std::string& key, const std::string& value) {
        data[key] = value;
    }
    std::string str() const {
        std::ostringstream oss;
        oss << "{";
        bool first = true;
        for (auto& kv : data) {
            if (!first) oss << ", ";
            oss << "\"" << kv.first << "\": \"" << kv.second << "\"";
            first = false;
        }
        oss << "}";
        return oss.str();
    }
};
