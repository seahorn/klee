#include "AddressSpace.h"
#include "Memory.h"

#include <stdio.h>
#include <sstream>
using namespace klee;

static std::string serialzeByteArray(uint8_t *base, int size) {
  std::string result = "";
  char buf[32];
  for (int i = 0; i < size; i++) {
    sprintf(buf, "0x%02x", base[i]);
    if (i < size - 1)
      result += std::string(buf) + ", ";
    else
      result += std::string(buf);
  }
  return result;
}
std::string AddressSpace::dumpAllObjects() const {
  std::ostringstream stringStream;
  for (MemoryMap::iterator it = objects.begin(), ie = objects.end(); it != ie;
       ++it) {
    const MemoryObject *mo = it->first;

    if (!mo->isUserSpecified) {
      ObjectState *os = it->second;
      uint8_t *address = (uint8_t *)(unsigned long)mo->address;
      char buf[256];
      sprintf(buf, "%p", address);

      stringStream << "{ " << buf << ": ["
                   << serialzeByteArray(os->concreteStore, mo->size)
                   << " ] } \n";
    }
  }
  return stringStream.str();
}