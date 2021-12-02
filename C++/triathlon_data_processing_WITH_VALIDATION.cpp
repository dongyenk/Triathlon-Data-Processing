/* This program takes triathlon data input as long as the user provides.
* It has proper input validation. If invalid input detected, an error message is displayed to the user and the bad data is handled. This allows input to continue normally after invalid input.
* Program exits once a negative number entered for an athlete's swim hours.
*
* This code uses a combination, of my knowledge and skills from University and self study.
* The input validation/error handling and for( type element_variable : container ) loop, are from my self study.
* Learned about how vectors are similar to arrays but are dynamic, because they grow and shrink as elements are added or removed, but I didn't use them here.
*/

//#define TESTING // removed preprocessor directive testing parts for tidier code

#include<iostream>
#include<string> // using std::string type && std::getline() function for input validation
//#include<vector> // learned about how arrays are static, std::vector<type> is dynamic
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
      std::string removed_line;
      std::getline( std::cin, removed_line );
    }
  }
}

int main(){
  const int8_t four = 4;
  const int8_t three = 3; // 8 bit integer types to save memory

  std::string athlete_name;
  unsigned long triathlon_seconds[ four ] = {0, 0, 0, 0};
  char * triathlon_names[ four ] = { "Swim", "Bike", "Run", "Total" }; // 0-3
  char * time_type_names[ three ] = { "hours", "minutes", "seconds" }; // 0-2

  const int8_t hours_index = 0;
  const int8_t minutes_index = 1;
  const int8_t seconds_index = 2;

  std::cout << "Athlete name:\t";  std::cin >> athlete_name;  std::cout << "\n"; // No input validation, because string holds anything

  for( int8_t event_i = 0; event_i < three; ++ event_i ){ // for triathlon event
    for( char * time_type : time_type_names ){ // for hr-min-sec
      std::cout << triathlon_names[ event_i ] << " " << time_type << ":";
      if( time_type == time_type_names[ hours_index ] ){
        triathlon_seconds[ event_i ] += convert_hours_or_minutes_to_seconds( handle_and_return_input() , 1 ); }
      else if( time_type == time_type_names[ minutes_index ] ){
        triathlon_seconds[ event_i ] += convert_hours_or_minutes_to_seconds( handle_and_return_input(), 0 );  }
      else if( time_type == time_type_names[ seconds_index ] ){
        triathlon_seconds[ event_i ] += handle_and_return_input();}
      std::cout << "\n";
    }// end of for hr-min-sec
    std::cout << "\n";
  }// end of for triathlon event
  return 0;
}
