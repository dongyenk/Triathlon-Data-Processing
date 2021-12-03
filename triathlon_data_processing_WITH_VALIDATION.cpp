/* This program takes triathlon data input as long as the user provides.
* For 1 athlete, input their hours, minutes, seconds, then name. <- Name at end, because exit condition makes inputting the name first, awkward.
* To exit, input negative number for swim hours.
* This code has proper input validation. If invalid input detected, an error message is displayed to the user and the bad data is handled. This allows input to continue normally after invalid input.
*
* This code uses a combination, of my knowledge and skills from University and self study.
* The input validation/error handling and for( type element_variable : container ) loop, are from my self study.
*/

//#define TESTING // removed preprocessor directive testing parts for tidier code
#include<iostream>
#include<string> // using std::string type && std::getline() function for input validation
#include<cmath>

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

int main(){
  const int8_t four = 4;
  const int8_t three = 3; // 8 bit integer types to save memory

  unsigned long triathlon_seconds[ four ] = {0, 0, 0, 0};
  char * triathlon_names[ four ] = { "Swim", "Bike", "Run", "Total" }; // 0-3
  char * time_type_names[ three ] = { "hours", "minutes", "seconds" }; // 0-2

  std::string athlete_name;
  std::string fastest_athlete_name;
  unsigned int fastest_athlete_seconds = int( std::pow( 2, 32 )  ); // maximum number that can be stored by unsigned int

  const int8_t hours_index = 0;
  const int8_t minutes_index = 1;
  const int8_t seconds_index = 2;
  const int8_t total_index = 3;

  bool negative_swim_hours = false;
  while( !negative_swim_hours ){
    for( int8_t event_i = 0; event_i < three; ++ event_i ){ // for triathlon event
      for( char * time_type : time_type_names ){ // for hr-min-sec
        std::cout << triathlon_names[ event_i ] << " " << time_type << ":";
        if( time_type == time_type_names[ hours_index ] ){
          int user_input = handle_and_return_input(); // End program if swim hours are negative.
          if( event_i == hours_index && user_input < 0){  negative_swim_hours = true; break; }
          triathlon_seconds[ event_i ] += convert_hours_or_minutes_to_seconds( user_input , 1 ); }
        else if( time_type == time_type_names[ minutes_index ] ){
          triathlon_seconds[ event_i ] += convert_hours_or_minutes_to_seconds( handle_and_return_input(), 0 );  }
        else if( time_type == time_type_names[ seconds_index ] ){
          triathlon_seconds[ event_i ] += handle_and_return_input();}
        std::cout << "\n";
      }// end of for hr-min-sec
      if( negative_swim_hours ){ break; }
      std::cout << "\n";
    }// end of for triathlon event
    if( negative_swim_hours ){ continue; } // Just using continue for practice

    std::string cleared_data; std::getline( std::cin, cleared_data ); // Moved athlete name code from top of while loop, as it made the negative swim hours condition awkward.
    std::cout << "Athlete name:\t";  std::getline(std::cin, athlete_name);  std::cout << "\n"; // No input validation, because string holds anything
             // std::cin >> x; only reads until the first white space. std::getline( stream, var ); reads (& removes from stream) whole line
    calculate_total_seconds( triathlon_seconds, three );
    display_times( triathlon_seconds, three, triathlon_names, athlete_name );

    if( triathlon_seconds[ total_index ] < fastest_athlete_seconds ){
      fastest_athlete_seconds = triathlon_seconds[ total_index ];
      fastest_athlete_name = athlete_name;
    }

    reset_array( triathlon_seconds, three ); // for the next athlete.
    // PROBLEM BETWEEN LOOPS. Can't input data for athlete name more than once. Going to try and fix by removing data from stream
    // std::string cleared_data;    std::getline( std::cin, cleared_data ); // works
  }
                                // converting to int, because comparing a float and int, made it not work.
  if( fastest_athlete_seconds < int( pow(2,32) ) ){ // Print message about fastest athlete, only if the default fastest seconds has been changed.
    int hr, min, sec;
    min = fastest_athlete_seconds / 60;    sec = fastest_athlete_seconds % 60;
    hr = min / 60;    min = min % 60;
    std::cout << "The fastest athlete is " << fastest_athlete_name << ", with the time:\t" << hr << "hr " << min << "min " << sec << "sec ";
  }

  return 0;
}
