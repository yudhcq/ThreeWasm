#include <stdexcept>
#include <time.h>
#include <stdlib.h>

#include "Guid.h"

using namespace std;

namespace Three
{
Guid::Guid()
{
    srand((unsigned int)time(NULL));
    mGuid[0] = static_cast<uint32_t>(static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * static_cast<double>(0xffffffffu));
    mGuid[1] = static_cast<uint32_t>(static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * static_cast<double>(0xffffffffu));
    mGuid[2] = static_cast<uint32_t>(static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * static_cast<double>(0xffffffffu));
    mGuid[3] = static_cast<uint32_t>(static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * static_cast<double>(0xffffffffu));
}

const string Guid::GetGuidString() const
{
    // todo
    return "";
}

void Guid::SetByByteArray(const vector<uint8_t> &guid)
{
    if (guid.size() < 16)
    {
        throw logic_error("Guid SetByByteArray guid len must be large than 16");
    }
    else
    {
        memcpy(mGuid, guid.data(), 16);
    }
}

void Guid::SetByGuidString(const string &guidStr)
{
    // todo
}

const vector<uint8_t> Guid::GetByteArray() const
{
    vector<uint8_t> _guid(16, 0);
    memcpy(_guid.data(), mGuid, 16);
    return move(_guid);
}

} // namespace Three
