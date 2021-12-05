// This header just declares functions. It uses macros to guard the header (prevent code being inserted multiple times)

#ifndef MY_FUNCTIONS
#define MY_FUNCTIONS

#include<string>

int convert_hours_or_minutes_to_seconds( int time, bool mode );
int handle_and_return_input();
void calculate_total_seconds( unsigned long seconds[], int8_t final_index );
void display_times( unsigned long seconds[], int8_t final_index, char * event_names[], std::string athlete_name );
void reset_array( unsigned long seconds[], int8_t final_index );

#endif
