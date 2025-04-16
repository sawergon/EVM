
#ifndef DIPLOMA_INCLUDE_OBJECTS_TRUSTCENTER_HPP_
#define DIPLOMA_INCLUDE_OBJECTS_TRUSTCENTER_HPP_
#include "../Network/Udp.hpp"
#include "../json.hpp"
#include <vector>

import Unital;
import PGpl2;
import PPdn;
import Fpld;
import Fpl;

using TCConfig = nlohmann::json;
class TrustCenter {
  public:
  /// центр строиться из Юнитала
  explicit TrustCenter( const TCConfig &config, const Unital &unital_ )
      : unital( unital_ ) {
    uBlocks.reserve( unital.getS() );
    ppBlocks.reserve( unital.getS() );
    fpldField   = unital.getField();
    auto [p, l] = findPLforPP( unital.getN() - 1 );
    fplField    = Fpl( p, l );
    fillUBlocks();   /// находим идентификаторв блоков доверенного центра
    fillPPBlocks();  /// находим соответствующие им идентификаторы блоков
                     /// проективной плоскости
  }

  void run();

  private:
  std::unique_ptr<Infrastructure::Network::UdpNetworkService> network;
  static std::pair<long, long> findPLforPP( long ppN );
  void                         fillUBlocks();
  void                         fillPPBlocks();
  std::vector<BlockId>         uBlocks;
  std::vector<PPBlockId>       ppBlocks;
  Unital                       unital;
  PPdn                         ppdn;
  Fpl                          fplField;
  Fpld                         fpldField;
};
#endif  // DIPLOMA_INCLUDE_OBJECTS_TRUSTCENTER_HPP_
