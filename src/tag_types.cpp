// Copyright (c) 2020, Manfred Moitzi
// License: MIT License
//
#include "tag_types.hpp"

ezdxf::TagType ezdxf::group_code_type(int code) {
    if ((code >= 10 && code < 19) ||
        (code >= 110 && code < 113) ||
        (code >= 210 && code < 214) ||
        (code >= 1010 && code < 1014))
        return ezdxf::TagType::VERTEX;

    if ((code >= 10 && code < 60) ||
        (code >= 110 && code < 150) ||
        (code >= 210 && code < 240) ||
        (code >= 460 && code < 470) ||
        (code >= 1010 && code < 1060)) {
        return ezdxf::TagType::DECIMAL;
    }
    if ((code >= 60 && code < 80) ||
        (code >= 90 && code < 100) ||
        (code >= 160 && code < 180) ||
        (code >= 270 && code < 290) ||
        (code >= 370 && code < 390) ||
        (code >= 400 && code < 410) ||
        (code >= 420 && code < 430) ||
        (code >= 440 && code < 460) ||
        (code >= 1060 && code < 1072))
        return ezdxf::TagType::INTEGER;
    return ezdxf::TagType::TEXT;
}

//ezdxf::TagType gcc_only(int code) {
//    switch (code) {
//        case 10 ... 18:
//        case 110 ... 112:
//        case 210 ... 213:
//        case 1010 ... 1013:
//            return ezdxf::TagType::VERTEX;
//        case 19 ... 59:
//        case 113 ... 149:
//        case 214 ... 239:
//        case 460 ... 469:
//        case 1014 ... 1059:
//            return ezdxf::TagType::DECIMAL;
//        case 60 ... 79:
//        case 90 ... 99:
//        case 160 ... 179:
//        case 270 ... 289:
//        case 370 ... 389:
//        case 400 ... 409:
//        case 420 ... 430:
//        case 440 ... 459:
//        case 1060 ... 1071:
//            return ezdxf::TagType::INTEGER;
//        default:
//            return ezdxf::TagType::TEXT;
//    }
//}