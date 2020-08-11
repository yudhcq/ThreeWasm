#pragma once
#include <stdint.h>
#include <string>
#include <vector>

namespace Three::Core
{
class Guid
{
public:
    Guid();
    const std::string GetGuidString() const;
    void SetByByteArray(const std::vector<uint8_t>& guid);
    void SetByGuidString(const std::string& guidStr);
    const std::vector<uint8_t> GetByteArray() const;
private:
    uint32_t mGuid[4];
};
} // namespace Three::Core
