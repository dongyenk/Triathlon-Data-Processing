/* This program takes user input about triathlon data, for as long as the user provides them
* Each loop through, the program handles input about 1 athlete. At the end of each loop, the program outputs information for the previous athlete.
* When the program has exited, and the user has inputted data about an athlete, the program outputs information about the fastest athlete.
* This program has very simple validation checking, meaning invalid input causes an exit.
* I've also included a struct, just for practice.
*/

#include <iostream>
#include <string>
#include <cmath>

int convert_hours_or_minutes_to_seconds( int time_value, bool mode ){
  if( mode ){
    return (time_value * 60) * 60;
  }
  else if( !mode ){
    return time_value * 60;
  }
  else{ return time_value; }
}

struct athlete_struct{
  std::string name;
  unsigned long total_seconds;
};

int check_invalid_input( bool invalid_input, bool extra_message = 0 ){
  if( extra_message ){ std::cout << "\n\Invalid Inputn"; }
  if( invalid_input ){ return 1; }
}

int main(){
  const int8_t three = 3;
  const int8_t four = 4;

  unsigned long triathlon_seconds[ four ] = {0, 0, 0, 0};
  char * triathlon_names[ four ] = { "Swim", "Bike", "Run", "Total" }; // 0-3
  char * time_names[ three ] = { "Hours", "Minutes", "Seconds" }; // 0-2

  const int8_t swim_or_hours_index = 0; // 8 bit intger data types for smaller numbers.
  const int8_t minutes_index = 1;
  const int8_t seconds_index = 2;
  const int8_t total_index = 3;

  std::string current_athlete_name;
  athlete_struct fastest_athlete;

  fastest_athlete.total_seconds = pow(2, 32); // maximum number that can be stored by 32 bit is 2^32

  std::cout << "To exit, input q for an athlete name, or input a negative number for swim hours. \nInvalid input at any point, also exits.\n\n";

  while( 1 ){

    bool negative_input = 0;
    bool invalid_input = 0;

    std::cout << "Athlete name:\t";
    std::cin >> current_athlete_name;
    //if( !std::cin ) Useless here. Any input can be assigned to the string.
    if( !current_athlete_name.compare( "q" ) ) // returns false if strings are equal
        { break; }

    for( int event_index = 0; event_index < three; event_index ++ ){
      for( int time_index = 0; time_index < three; time_index ++ ){
        std::cout << triathlon_names[ event_index ] << " " << time_names[ time_index ] << ":\t";

        int user_input = 0;

        std::cin >> user_input; // Exit the loops if invalid input is made, or if negative entered for swim hours.
        if( !std::cin ){ // I know std::cin has a .clear() function that clears its fail state, but it doesn't remove the bad data.
          invalid_input = 1; // this variable in the scope of other loops
        }
        if( user_input < 0 && event_index == 0 && time_index == 0){
          negative_input = 1;
        } // Above 2 if statements set a boolean variable to true. Below if statement checks if either is true, to determine if it should break out the loop.

        if( invalid_input || negative_input){ break; } // breaks out the time for loop

        int seconds_to_add = 0;

        switch( time_index ){
          case swim_or_hours_index:
            seconds_to_add = convert_hours_or_minutes_to_seconds( user_input, 1 ); // 1 evaluates as true boolean
            break;
          case minutes_index:
            seconds_to_add = convert_hours_or_minutes_to_seconds( user_input, 0 );
            break;
          case seconds_index:
            seconds_to_add = user_input;
            break;
          default:
            // seconds_to_add == 0
            break;
         }
         triathlon_seconds[ event_index ] += seconds_to_add;
      } // END OF SECONDS FOR LOOP
      std::cout << "\n";
      if( invalid_input || negative_input ){ break; } // breaks out of the event for loop
    }// END OF EVENT FOR LOOP. If complete, should have array of swim-bike-run seconds.

    if( invalid_input ){
      std::cout << "\nInvalid Input.\n";
      //break; <- This causes main to return 0
      return 1; // exits while loop. While loop returns 1, which causes main function to exit early.
    }
    if( negative_input ){
      std::cout << "Negative Input Made for Swim Hours. Program Exiting.\n";
      break; // Just breaks out of while loop. Doesn't exit main.
    }

    for( int seconds_array_index = 0; seconds_array_index < three; seconds_array_index ++ ){
      triathlon_seconds[ three ] += triathlon_seconds[ seconds_index ];
    }

    for( int seconds_array_index = 0; seconds_array_index < four; seconds_array_index ++ ){
      // Output information about hours, minutes, seconds of each athelete.
      int minutes = triathlon_seconds[ seconds_array_index ] / 60;
      int seconds = triathlon_seconds[ seconds_array_index ] % 60;
      int hours = minutes / 60;
      minutes = minutes % 60;
      // triathlon_seconds indexes correspond with those of triathlon_names
      std::cout << triathlon_names[ seconds_array_index ] << " times:\t" << hours << "hr " << minutes << "min " << seconds << "sec\n\n";
    }

    if( triathlon_seconds[ total_index ] < fastest_athlete.total_seconds){
      fastest_athlete.total_seconds = triathlon_seconds[ total_index ]; // only changes the variable, if the total seconds are less
      fastest_athlete.name = current_athlete_name;
    }

    for( int i = 0; i < four; i ++ ){ // RESETTING SECONDS ARRAY
      triathlon_seconds[ i ] = 0;
    }

  } // END OF WHILE LOOP

  // TODO, info about fastest athlete. + their name would be nice.
  if( fastest_athlete.total_seconds < pow(2, 32) ){ // ONLY IF THE FASTEST SECONDS VALUE IS LESS THAN THE DEFAULT MAXIMUM
    int fastest_minutes = fastest_athlete.total_seconds / 60;
    int fastest_seconds = fastest_athlete.total_seconds % 60;

    int fastest_hours = fastest_minutes / 60;
    fastest_minutes = fastest_minutes % 60;

    std::cout << "\nThe fastest athlete was " << fastest_athlete.name << ", with a time of " << fastest_hours << "hr " << fastest_minutes << "min " << fastest_seconds << "sec.\n";
  }

  return 0;
} // END OF MAIN
