// Copyright (c) 2020, Manfred Moitzi
// License: MIT License
//
#ifndef EZDXF_UTILS_HPP
#define EZDXF_UTILS_HPP

#include <optional>
#include <initializer_list>
#include "ezdxf/type.hpp"
#include "ezdxf/simple_set.hpp"


namespace ezdxf::utils {
    void ltrim(String &s);

    void rtrim(String &s);

    void trim(String &s);

    void rtrim_endl(String &s);

    // Important note:
    // This converters are optimized to load DXF tags and nothing else,
    // they are not meant as general purpose functions.

    std::optional<Real> safe_str_to_real(const String &s);

    std::optional<int64_t> safe_str_to_int64(const String &s);

    int safe_group_code(const String &s);

    // Utility functions to manage binary data in binary tags with
    // group codes 310-319 & 1004.
    String hexlify(const Bytes &data);

    std::optional<Bytes> unhexlify(String s);

    Bytes concatenate_bytes(const std::vector<Bytes> &data);

    String dxf_version_to_str(Version v);

    Version str_to_dxf_version(String s);

    extern const SimpleSet<Version> DXFExportVersions;
}
#endif //EZDXF_UTILS_HPP
