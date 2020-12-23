// Copyright (c) 2020, Manfred Moitzi
// License: MIT License
//
#include <unordered_map>
#include "tag_types.hpp"

namespace ezdxf {
    static auto group_code_cache = std::unordered_map<int, TagType>(); // NOLINT(cert-err58-cpp)

    TagType group_code_type(int code) {
        auto it = group_code_cache.find(code);
        if (it != group_code_cache.end()) {
            return it->second;
        }
        TagType tag_type = TagType::TEXT; // default value
        if ((code >= 10 && code < 19) ||
            (code >= 110 && code < 113) ||
            (code >= 210 && code < 214) ||
            (code >= 1010 && code < 1014)) {
            tag_type = TagType::VERTEX;
        } else if ((code >= 19 && code < 60) ||
                   (code >= 113 && code < 150) ||
                   (code >= 214 && code < 240) ||
                   (code >= 460 && code < 470) ||
                   (code >= 1014 && code < 1060)) {
            tag_type = TagType::DECIMAL;
        } else if ((code >= 60 && code < 80) ||
                   (code >= 90 && code < 100) ||
                   (code >= 160 && code < 180) ||
                   (code >= 270 && code < 290) ||
                   (code >= 370 && code < 390) ||
                   (code >= 400 && code < 410) ||
                   (code >= 420 && code < 430) ||
                   (code >= 440 && code < 460) ||
                   (code >= 1060 && code < 1072)) {
            tag_type = TagType::INTEGER;
        }
        group_code_cache.insert({code, tag_type});
        return tag_type;
    }
}
