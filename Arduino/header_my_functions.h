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
