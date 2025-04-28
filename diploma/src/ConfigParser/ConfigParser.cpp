#include "ConfigParser.hpp"

namespace parser {
  t_TablePtr parse( const nlohmann::json &json ) {
    if ( !json.contains( "data" ) )
      return nullptr;
    const auto &data = json["data"];
    if ( !data.is_array() )
      return nullptr;
    t_TablePtr table = std::make_shared<t_Table>();
    for ( const auto &item : data ) {
      if ( !item.contains( "idRouter" ) )
        continue;
      if ( !item.contains( "connectWith" ) )
        continue;
      const auto &idRouter    = item["idRouter"];
      const auto &connectWith = item["connectWith"];
      if ( !idRouter.is_number() )
        continue;
      if ( !connectWith.is_array() )
        continue;
      table->insert(
          { idRouter.get<size_t>(), connectWith.get<std::list<size_t>>() } );
    }
    return table;
  }
}  // namespace parser