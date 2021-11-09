/* This is just from very early stages of recreating the data processing code from the Arduino, in C++.
* TODO: implement input handling. Then input validation to be fancy.
*/

#define DEBUG

#include <iostream> // for std::cout
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

int main(){
  const int four = 4;
  const int three = 3;

  unsigned long swim_bike_run_total_seconds[ four ] = { 0, 0, 0, 0 }; // 4 indexes, from 0 to 3
    // index 0-swim, 1-bike, 2-run, 3-total. For seconds and name array :).
  std::string swim_bike_run_total_names[ four ] = { "Swim", "Bike", "Run", "Total" }; // to be used for eZ for loop message printing.

  std::string hr_min_sec_time_types[ three ] = { "hours", "minutes", "seconds" };
  // defining constants to check with, and determine how to convert input to seconds.
  const int hours_index = 0;    const int minutes_index = 1;    const int seconds_index = 2;

  #ifdef DEBUG // ifdef <TOKEN> #endif, allow preprocessor to omit blocks of code for compiler
    debug_messages_1( four, three, swim_bike_run_total_seconds, swim_bike_run_total_names, hr_min_sec_time_types );
  #endif // DEBUG

  // per 1 athelete for each event, ask for hr-min-sec.
  for( int event_index = 0; event_index < three; event_index ++ ){
    for( int time_index = 0; time_index < three; time_index ++ ){
      std::cout << swim_bike_run_total_names[ event_index ] << " " << hr_min_sec_time_types[ time_index ] << ": ";
      // add user input, converted to seconds, to the seconds array[ event_index ]. check time type asked for, to know how to convert to seconds.
      switch( time_index ){
        // switch case block, seems a lot like an alternate if-else if-else chain
        case hours_index: //0
          break;
        case minutes_index: // 1
          break;
        case seconds_index: // 2
          break;
        default:
          swim_bike_run_total_seconds[ event_index ] += 0;
      }
      std::cout << "\n";
    } // END OF TIME FOR LOOP
    std::cout << "\n";
  }// END OF EVENT FOR LOOP

  return 0;
}
