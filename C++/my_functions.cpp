#include "my_functions.hpp"
#include <iostream>
#include <string>

int convert_hours_or_minutes_to_seconds( int time, bool mode ){
// 1 for hours, 0 for minutes
  if( mode ){ return ( time * 60 ) * 60; }
  else if( !mode ){
    return time * 60;
  }
  else{ return time; }
}
int handle_and_return_input(){ // seems to work
  int user_input;
  while( 1 ){
    std::cout << "\t";
    std::cin >> user_input;
    if( !std::cin ){ // if stream evaluates as false/in fail state, clear error flags, remove bad input, display error message.
      std::cin.clear(); // .clear() only removes error flags, not the bad data line from the stream.
      std::string error_line;
      std::getline( std::cin, error_line ); // this function removes bad data from stream, and assigns to variable
      std::cout << "Invalid Input:\t" << error_line << "\nTry Again.\n";
      continue; // statement not necessary in this specific case
    }
    else if( std::cin ){ // break out of loop and return value, if input valid
      return user_input; // return should break main loop,
    }
  }
}

void calculate_total_seconds( unsigned long seconds[], int8_t final_index ){
  for( int8_t i = 0; i < final_index; ++ i ){
    seconds[ final_index ] += seconds[ i ];  }
}
void display_times( unsigned long seconds[], int8_t final_index, char * event_names[], std::string athlete_name ){
  std::cout << "Athlete:\t" << athlete_name << "\n";
  int hr, min, sec;
  for( int8_t i = 0; i <= final_index; i ++ ){
    min = seconds[ i ] / 60;    sec = seconds[ i ] % 60;
    hr = min / 60;          min = min % 60; // % 60 goes in an integer number of times, and the remainder is ....
    std::cout << event_names[ i ] << " times:\t" << hr << "hr " << min << "min " << sec << "sec " << "\n";
  }std::cout << "\n";
}
void reset_array( unsigned long seconds[], int8_t final_index ){
  for( int8_t i = 0; i <= final_index; ++ i ){
    seconds[ i ] = 0;  }
}
