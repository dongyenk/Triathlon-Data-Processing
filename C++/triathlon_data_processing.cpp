/* This is just from very early stages of recreating the data processing code from the Arduino, in C++.
* TODO: implement input handling. Then input validation to be fancy.
*/

//#define DEBUG // The debug_mesages_1 function doesn't work, when char pointer arrays are used.

#define USE_CHAR_POINTER // define to use arrays of char *, instead of arrays of std::string.

#include <iostream> // for std::cout && std::cin
#include <string> // for std::string

void debug_messages_1( int four, int three, unsigned long swim_bike_run_total_seconds[], std::string swim_bike_run_total_names[], std::string hr_min_sec_time_types[] ){
  for( int i = 0; i < four; i ++ ){
    std::cout << swim_bike_run_total_names[ i ] << "\n\t" << swim_bike_run_total_seconds[ i ] << "\n";
    if( i < three ){
      std::cout << "\t\t" << hr_min_sec_time_types[ i ] << "\n";
    } // condition must evaluate as true for if block to execute, or for loop to loop.
  }
  std::cout << "\n";
}
int handle_and_return_input(){
  int input;
  std::cin >> input;
  return input;
}

int convert_hours_or_minutes_to_seconds( int time_value, bool mode ){
  // 1 for hours, 0 for minutees. 1 evaluates as true, 0 false
  if( mode ){
    return ( time_value * 60 ) * 60;
  }
  else if( !mode ){
    return time_value * 60;
  }
  else{ return time_value; }
}

void calculate_and_assign_total_seconds( unsigned long swim_bike_run_total_seconds[], int three ){
  for( int seconds_array_index = 0; seconds_array_index < three; seconds_array_index ++ ){
    swim_bike_run_total_seconds[ three ] += swim_bike_run_total_seconds[ seconds_array_index ]; // for loop incrementing total seconds value
  }
}

void reset_seconds_array( unsigned long swim_bike_run_total_seconds[], int four ){
  for( int i = 0; i < four; i ++ ){
    swim_bike_run_total_seconds[i] = 0;
  }
}

int main(){
  const int four = 4;
  const int three = 3;

  unsigned long swim_bike_run_total_seconds[ four ] = { 0, 0, 0, 0 }; // 4 indexes, from 0 to 3
    // index 0-swim, 1-bike, 2-run, 3-total. For seconds and name array :).
  #ifdef USE_CHAR_POINTER
    char * swim_bike_run_total_names[ four ] = { "Swim", "Bike", "Run", "Total" }; // arrays of pointers to first char in the strings
    char * hr_min_sec_time_types[ three ] = { "hours", "minutes", "seconds" };     // call index of these arrays, to get full string
  #else
    std::string swim_bike_run_total_names[ four ] = { "Swim", "Bike", "Run", "Total" }; // std::string requires more memory than a char *?
    std::string hr_min_sec_time_types[ three ] = { "hours", "minutes", "seconds" };
  #endif

  // defining constants to check with, and determine how to convert input to seconds.
  const int hours_or_swim_index = 0;    const int minutes_index = 1;    const int seconds_index = 2;

  #ifdef DEBUG
    debug_messages_1( four, three, swim_bike_run_total_seconds, swim_bike_run_total_names, hr_min_sec_time_types );
  #endif // Function doesn't work if char pointer arrays used.

  while( 1 ){ //while(true)
    // Each while loop handles input && data for 1 athlete
    // IMPLEMENT : Loop exits when user inputs negative number for swim hours. A break; in the time for loop, would only break the local loop.
    bool negative_input = false;

    for( int event_index = 0; event_index < three; event_index ++ ){
      for( int time_index = 0; time_index < three; time_index ++ ){
        std::cout << swim_bike_run_total_names[ event_index ] << " " << hr_min_sec_time_types[ time_index ] << ": ";

        int input = handle_and_return_input();

        if( event_index == hours_or_swim_index && time_index == hours_or_swim_index && input < 0 ){
          negative_input = true;
          break; // breaks out of time for loop
        }

        // add user input, converted to seconds, to the seconds array[ event_index ]. check time type asked for, to know how to convert to seconds.
        switch( time_index ){
          // switch case block, seems a lot like an alternate if-else if-else chain
          case hours_or_swim_index: //0
            // IMPLEMENT. Functions to handle && return input. Convert hours or mins to seconds. Then add seconds to array[eventindex]
            swim_bike_run_total_seconds[event_index] += convert_hours_or_minutes_to_seconds( input, 1 );
            break; // break && return statements break out of their local block of code.
          case minutes_index: // 1
            swim_bike_run_total_seconds[event_index] += convert_hours_or_minutes_to_seconds( input, 0 );
            break;
          case seconds_index: // 2
            swim_bike_run_total_seconds[event_index] += input;
            break;
          default:
            swim_bike_run_total_seconds[ event_index ] += 0;
        }
        std::cout << "\n";
      } // END OF TIME FOR LOOP
      std::cout << "\n";
      if( negative_input ){
        break; // breaks out of event for loop
      }
    }// END OF EVENT FOR LOOP. Once complete, should have seconds array, with values for swim-bike-run, but not total

    if( negative_input ){
      std::cout << "\nExiting Program\n";
      break;
    }

    calculate_and_assign_total_seconds( swim_bike_run_total_seconds, three );

    for( int seconds_array_index = 0; seconds_array_index < four; seconds_array_index ++ ){
      // DIV and MOD operations to find integer quotients && remainders (e.g. how many unnacounted minutes in seconds value, && the remainder)
      int minutes = swim_bike_run_total_seconds[ seconds_array_index ] / 60;
      int seconds = swim_bike_run_total_seconds[ seconds_array_index ] % 60; //    / -> fits in, integer number of times. % -> remainder
      int hours = minutes / 60;
      minutes = minutes % 60;

      std::cout << swim_bike_run_total_names[seconds_array_index] << " time: " << hours << "hr " << minutes << "min " << seconds << "sec \n";
    }
    reset_seconds_array( swim_bike_run_total_seconds, four ); // the seconds add up for all athletes other wise
    std::cout << "\n";
  }

  return 0;
}
