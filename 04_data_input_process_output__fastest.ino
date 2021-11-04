#define DEBUG

#include "02_my_functions.h"

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
  bool negative_input = 0; // 0 evaluates as false boolean, >=1 as true

  unsigned long fastest_athelete_total_seconds = 4000000; // this only changes if total seconds is less than the variable's value
  byte fastest_athelete_number; // in same if block as above; assign value for this

  while( 1 ){ // in a while( true ) or while( 1 ) loop, the code must explicitly break the loop, as the condition can't change
    #ifdef DEBUG
      Serial.print("\t\tathelete_number: "); Serial.println(athelete_number); // combining values to print in a single print function here, causes it to not work :/
      Serial.print("\t\tnegative_input: "); Serial.println(negative_input);
    #endif

    for( byte event_index = 0; event_index < time_types_or_total_index; event_index ++ ){ // determines which arrays index is accessed
      #ifdef DEBUG
        Serial.print("\t\tevent_index: "); Serial.println(event_index);
      #endif

      for( byte time_index = 0; time_index < time_types_or_total_index; time_index ++ ){ // determines how user input is processed
        #ifdef DEBUG
          Serial.print("\t\ttime_index: "); Serial.println(time_index);
        #endif

        Serial.print( swim_bike_run_total_strings[ event_index ] + " " + hr_min_sec_time_types[ time_index ] + ": " );
        
        int user_input = handle_and_return_input(); // Convert value to seconds, using different processes, depending on time_index/time type asked for ( hr-min-sec )
        // assigning input to variable, so I can check if it's negative, when user inputs value for swim hours
        if( event_index == swim_or_hours_index && time_index == swim_or_hours_index && user_input < 0 ){
          negative_input = 1;             // EXIT THE PROGRAM, WHEN USER ENTERS NEGATIVE NUMBER FOR SWIM HOURS
          break; // only breaks the hr-min-sec for loop, so I defined a variable in the scope of all the loops.
        }
        int seconds_to_add_on;
        // Using a switch case block instead of an if-else if-else chain          
        switch( time_index ){
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
      if( negative_input ){
        break; // breaks swim-bike-sec events for loop
      }
      Serial.println();
    }// END OF EVENT FOR LOOP // End of loop asking about 1 athelete, and their hr-min-sec for swim-bike-run /
    
    if( negative_input ){
      Serial.println();
      Serial.println("Program Exited :)");
      break; // breaks while loop
    }

    calculate_total_seconds( swim_bike_run_total_seconds, time_types_or_total_index );    
    // at this stage, we have an array of unsigned long datatypes, storing the seconds of swim,bike,run,total    

    if( swim_bike_run_total_seconds[ time_types_or_total_index ] < fastest_athelete_total_seconds && swim_bike_run_total_seconds[ time_types_or_total_index ] > 0 ){
      fastest_athelete_total_seconds = swim_bike_run_total_seconds[ time_types_or_total_index ];
      fastest_athelete_number = athelete_number;
    }

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

    // Output information about the fastest athelete! // but only if the fastest atheletes total second value has been changed!!
  if( fastest_athelete_total_seconds < 4000000 ){
    int minutes = fastest_athelete_total_seconds / 60;
    int seconds = fastest_athelete_total_seconds % 60;
    int hours = minutes / 60;
    minutes = minutes % 60;
                  // I was getting strange errors again, caused by giving the print function, multiple arguments
    Serial.print("The fastest was athelete no."); Serial.print( fastest_athelete_number ); Serial.print(", with a total time of ");
    Serial.print(hours); Serial.print(" hours, "); Serial.print(minutes); Serial.print(" minutes, "); Serial.print( seconds ); Serial.println(" seconds.");
  }
}

void loop(){}
