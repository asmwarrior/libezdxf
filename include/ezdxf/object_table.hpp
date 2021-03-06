// Copyright (c) 2021, Manfred Moitzi
// License: MIT License
//
#ifndef EZDXF_OBJECT_TABLE_HPP
#define EZDXF_OBJECT_TABLE_HPP

#include <stdexcept>
#include <vector>
#include <memory>
#include "ezdxf/type.hpp"
#include "ezdxf/acdb/object.hpp"

namespace ezdxf {
    using ezdxf::Handle;
    using ezdxf::acdb::Object;


    template<int N = 12>  // 2^12 = 4096 buckets
    class ObjectTable {
        // The ObjectTable is the central storage for all DXF objects which
        // have a handle (not DXF Class!). The table store ther objects as
        // unique pointers and therefore owns the objects and destroys all
        // objects at the end of it's lifetime.
        //
        // Goal: A compact and fast enough DXF object lookup by handle.
        // Relationship between handle and object is fixed and does not
        // change over the lifetime of a document and DXF objects will also not
        // destroyed, therefore deleting table entries is not required.
        // Table size is fixed and will not grow over runtime.

    private:
        struct TableEntry {
            Handle handle{};
            std::unique_ptr<Object> object{};
        };
        using Bucket = std::vector<TableEntry>;

        constexpr int count = 1 << N;  // fixed count of buckets as power of 2
        constexpr uint64_t hash_mask = count - 1;
        std::vector<Bucket> buckets{count};
        Handle max_handle_{0}; // biggest stored handle
        std::size_t size_{0};  // count of DXF objects stored

        [[nodiscard]] Bucket get_bucket(Handle const handle) const {
            return buckets[handle & hash_mask];
        };

    public:
        [[nodiscard]] std::size_t size() const { return size_; }

        // "get()" is the most important function here:
        Object *
        get(Handle const handle, Object const *const default_ = nullptr) const {
            // Returns a reference to a DXF object.
            // Does not transfer ownership!
            for (TableEntry const &entry : get_bucket(handle)) {
                // Linear search is fast for small vectors!
                if (entry.handle == handle) return entry.object.get();
            }
            return default_;
        }

        Handle aquire_free_handle() {
            // Return next unused handle. The object table does not return the
            // same handle again, but does not prevent adding objects using
            // that handles.
            return ++max_handle_;
        }

        [[nodiscard]] inline bool has(Handle const handle) const {
            // Returns true if a DXF object referenced by handle is stored
            // in the object table.

            // The "0" handle is an invalid handle per definition
            return handle != 0 && get(handle) != nullptr;
        }

        [[nodiscard]] inline bool contains(Object const *const object) const {
            // Returns true if the DXF object is stored in the object table.
            return has(object->get_handle());
        }

        void store(std::unique_ptr<Object> object) {
            // Transfer ownership of the DXF object to the object table.
            Handle handle = object->get_handle();
            // The "0" handle is an invalid handle per definition
            if (handle == 0)
                throw (std::invalid_argument("object handle 0 is invalid"));
            if (!has(handle)) { // Transfer ownership:
                get_bucket(handle).emplace_pack(handle, object);
                ++size_;
                if (handle > max_handle_) max_handle_ = handle;
            } else
                throw (std::invalid_argument(
                        "object with same handle already exist"));
        }
    }
}
#endif //EZDXF_OBJECT_TABLE_HPP
