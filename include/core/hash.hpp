#ifndef SIMPLE_LOG_HASH_HPP
#define SIMPLE_LOG_HASH_HPP

#include <string>
#include <cstdint>
#include <vector>

namespace SimpleLog
{
  
inline uint64_t hash64(const std::string& s) 
{
    uint64_t hash = 1469598103934665603ULL; // FNV offset basis
    const uint64_t prime = 1099511628211ULL; // FNV prime

    for (unsigned char c : s) 
    {
        hash ^= c;
        hash *= prime;
    }
    return hash;
}

inline std::vector<uint64_t> hash64(const std::vector<std::string>& ss)
{
    std::vector<uint64_t> hashes;
    hashes.reserve(ss.size());
    for (const auto& s : ss)
    {
        hashes.push_back(hash64(s));
    }
    return hashes;
}

}

#endif // SIMPLE_LOG_HASH_HPP