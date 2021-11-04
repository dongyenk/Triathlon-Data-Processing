/* This program allows the user to input triathlon time result data about atheletes.
* Once the user has input the hr-min-sec time values for an athelete, the program will output processed data about the athelete, in a nice format.
* Once data for 1 athelete has been entered, the program prompts for input on the next.
* In a university class, I made basically the same program, but in my free time, I experimented with, and improved the code.
* The next version of this program, will allow the user to exit, by inputting a negative number, for swim hours.
*/

int handle_and_return_input(){
  while( !Serial.available() ){ // inverse of Serial.available() evaluates as true
    // while loop of doing nothing, while there's no data in the serial port, and Serial.available() evaluates as false
  }
  return Serial.parseInt(); // as well as returning data, Serial.parseInt() removes data from the serial port, and makes S.available() evaluate as false again 
}
int convert_hours_or_minutes_to_seconds( int time_value, bool mode = 0 ){
  // 1 for hours, 0 for minutes
  if( mode == 1 ){
    return ( time_value * 60 ) * 60;
  }
  else if( mode == 0 ){
    return time_value * 60;
  }
}
void calculate_total_seconds( unsigned long swim_bike_run_total_seconds[], byte time_types_or_total_index ){
  for( byte seconds_array_index = 0; seconds_array_index < time_types_or_total_index; seconds_array_index ++ ){
    // increment value of total seconds index, by value of previous 3 indexes (0,1,2)
    swim_bike_run_total_seconds[ time_types_or_total_index ] += swim_bike_run_total_seconds[ seconds_array_index ];
  }
}
void reset_seconds_array( unsigned long swim_bike_run_total_seconds[], byte event_array_indexes ){
  for( byte seconds_array = 0; seconds_array < event_array_indexes; seconds_array ++ ){
    swim_bike_run_total_seconds[ seconds_array ] = 0;
  }
}

void setup(){  
  Serial.begin(9600);
  
  const byte event_array_indexes = 4;
  const byte time_types_or_total_index = 3;

  unsigned long swim_bike_run_total_seconds[ event_array_indexes ] = {0, 0, 0, 0};
  String swim_bike_run_total_strings[ event_array_indexes ] = { "Swim", "Bike", "Run", "Total" };
  String hr_min_sec_time_types[ time_types_or_total_index ] = { "hours", "minutes", "seconds" };

  const byte swim_or_hours_index = 0;
  const byte bike_or_minutes_index = 1;
  const byte run_or_seconds_index = 2;
  // const byte total_index = 3;

  byte athelete_number = 1;  

  while( 1 ){
    for( byte event_index = 0; event_index < time_types_or_total_index; event_index ++ ){
      for( byte time_index = 0; time_index < time_types_or_total_index; time_index ++ ){
        Serial.print( swim_bike_run_total_strings[ event_index ] + " " + hr_min_sec_time_types[ time_index ] + ": " );
        
        int user_input = handle_and_return_input(); // Convert value to seconds, using different processes, depending on time_index/time type asked for ( hr-min-sec )
        // assigning input to variable, so I can check if it's negative, when user inputs value for swim hours
        
        int seconds_to_add_on;
        switch( time_index ){// Using a switch case block instead of an if-else if-else chain          
          case swim_or_hours_index: // basically asking, if time_index == 0
            seconds_to_add_on = convert_hours_or_minutes_to_seconds( user_input, 1 ); // hr -> min -> sec
            break; // use either break; or return <val>; to break a switch case
          case bike_or_minutes_index:
            seconds_to_add_on = convert_hours_or_minutes_to_seconds( user_input, 0 ); // min -> sec
            break;
          case run_or_seconds_index:
            seconds_to_add_on = user_input; // sec
            break;
          default:
            seconds_to_add_on = 0;      
            break;
        }
        swim_bike_run_total_seconds[ event_index ] += seconds_to_add_on;
        
        Serial.println();
      }// END OF FOR TIME LOOP // asking about hr-min-sec of an event by 1 athelete

      Serial.println();
    }// END OF EVENT FOR LOOP // End of loop asking about 1 athelete, and their hr-min-sec for swim-bike-run /
    calculate_total_seconds( swim_bike_run_total_seconds, time_types_or_total_index );
    // time to output hr-min-sec of swim-bike-run-total by 1 athelete. 
    for( byte event_index = 0; event_index < event_array_indexes; event_index ++ ){
      // event_index, 0-3, to access seconds array indexes, and event names array indexes!
      int minutes = swim_bike_run_total_seconds[ event_index ] / 60;
      int seconds = swim_bike_run_total_seconds[ event_index ] % 60;
      int hours = minutes / 60; // DIV and MOD operations to find integer number of times 60 fits in, and the remainder.
      minutes = minutes % 60;
      
      Serial.println( swim_bike_run_total_strings[ event_index ] + " times: " + hours + "hr " + minutes  + "min " + seconds + "sec " );
    }
    Serial.println();
    reset_seconds_array( swim_bike_run_total_seconds, event_array_indexes );  // Must reset seconds array values after each athelete, else times from atheletes add up 

    athelete_number += 1;
  }// END OF WHILE LOOP // Each new loop through gets data about another athelete
}

void loop(){}
