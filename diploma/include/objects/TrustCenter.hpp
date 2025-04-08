
#ifndef DIPLOMA_INCLUDE_OBJECTS_TRUSTCENTER_HPP_
#define DIPLOMA_INCLUDE_OBJECTS_TRUSTCENTER_HPP_
#include <vector>

import Unital;
import PGpl2;
import PPdn;
import Fpld;
import Fpl;

class TrustCenter {
  public:
      /// центр строиться из Юнитала
      TrustCenter(const Unital& unital_) {
        unital = unital_;
        uBlocks.reserve(unital.getS());
        ppBlocks.reserve(unital.getS());
        fpldField = unital.getField();
        auto [p, l] = findPLforPP(unital.getN() - 1);
        fplField = Fpl(p, l);
        fillUBlocks(); /// находим идентификаторв блоков доверенного центра
        fillPPBlocks(); /// находим соответствующие им идентификаторы блоков проективной плоскости
      }
  private:
      static std::pair<long, long> findPLforPP(long ppN);
      void fillUBlocks();
      void fillPPBlocks();
      std::vector<BlockId> uBlocks;
      std::vector<PPBlockId> ppBlocks;
      Unital unital;
      Fpl fplField;
      Fpld fpldField;
};
#endif  // DIPLOMA_INCLUDE_OBJECTS_TRUSTCENTER_HPP_
