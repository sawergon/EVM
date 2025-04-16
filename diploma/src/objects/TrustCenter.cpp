#include "TrustCenter.hpp"
#include <NTL/ZZ_p.h>

std::pair<long, long> TrustCenter::findPLforPP( long ppN ) {
  long p = 1, l;
  for ( ; p < ppN; ++p ) {
    for ( l = 1; l < 4; ++l ) {
      if ( NTL::power_long( p, l ) == ppN ) {
        return { p, l };
      }
    }
  }
  return { 0, 0 };
}
void TrustCenter::fillUBlocks() {
  for (long i = 0; i < uBlocks.size(); ++i) {
    uBlocks.emplace_back(unital.getBlockId(i));
  }
}
void TrustCenter::fillPPBlocks() {
  for (long i = 0; i < ppBlocks.size(); ++i) {
    ppBlocks.emplace_back(ppdn.getBlockId(i));
  }
}
