#include "ConfigParser.hpp"
#include "Model.hpp"
#include <fstream>
#include <iostream>

void printMenu() {
  std::cout << "1. send msg" << std::endl;
  std::cout << "2. view network" << std::endl;
  std::cout << "enter \'q\' to quite" << std::endl;
  std::cout << "$> ";
}

void startMenu( model::Model &model ) {
  std::string command;
  while ( true ) {
    printMenu();
    std::getline( std::cin, command );
    if ( command == "1" ) {
      std::cout << "Enter from uni id:" << std::endl;
      std::cout << "$> ";
      long from;
      while ( !( std::cin >> from ) ) {
        std::cout << "Incorrect input. Please enter number:" << std::endl;
        std::cout << "$> ";
        std::cin.clear();
        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
      }
      std::cout << "Enter to uni id:" << std::endl;
      std::cout << "$> ";
      long to;
      while ( !( std::cin >> to ) ) {
        std::cout << "Incorrect input. Please enter number:" << std::endl;
        std::cout << "$> ";
        std::cin.clear();
        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
      }
      std::cout << "Enter message:" << std::endl;
      std::cout << "$> ";
      std::string msg;
      std::getline( std::cin, msg );
      std::getline( std::cin, msg );
      model.send( from, to, msg );
    }
    else if ( command == "2" ) {
      model.printNetwork();
    } else if (command == "q" || command == "exit") {
      std::cout << "Bye" << std::endl;
      break;
    } else {
      std::cout << "Unknown command" << std::endl;
    }
  }
}

int main( int argc, char *argv[] ) {
  if ( argc < 2 ) {
    std::cout << "No config file provided" << std::endl;
    return 1;
  }
  nlohmann::json config;
  std::fstream   in( argv[1] );
  in >> config;
  auto result = parser::parse( config );
  if ( !result ) {
    return 1;
  }

  model::coordinator::uniParams uni_params = { config["unital_params"]["p"],
                                               config["unital_params"]["l"],
                                               config["unital_params"]["d"] };

  model::Model model(
      uni_params, result,
      []( const std::string &msg ) { std::cout << msg << std::endl; }, false );

  startMenu(model);
  return 0;
}