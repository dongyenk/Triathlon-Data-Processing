__**INTRODUCTION**__
----------------------
  This repository contains programs, that receive data input, process the data, then output useful data to the user. Some of the files will be based on work I did in Univerisity classes,
  but I have improved the code, and done some experimentation.
  
__**FOLDERS**__
The 'Arduino' folder contains programs made in the Arduino IDE, and for the Arduino. Programs here are more closely related to things I did in university.

The  'C++' folder will contain functionally similar software, that uses more of my knowledge from self study.

__**FILE NAMES**__
---------------------
File names will begin with 2 numbers.
E.g. "01_data_processing.ino", will have the oldest code I typed, and just be an improved version of a program I made in a class. And, "17_data_processing.ino", will be a more recent program, that I did in my own time, that uses more of my self study knowledge.

__**HEADER FILES**__
----------------------------
These files have the "header_" prefix, and ".h" suffix. If a source file (.ino or .cpp) uses a header file:

	it's '#include "{header_file_name}"' preprocessor statement will be, will be at the top.
	Whatever header file is specified here, will be required for the source file to compile.
I have learned that I used a header file wrong, by defining functions inside it.

__**FILE TYPES**__
----------------------
.ino files are programs made in the Arduino IDE, that require the IDE, and an Arduino, to compile. The Arduino IDE serial monitor can't handle input, unless the "newline" setting is changed to "no line ending".

__**COMMENTS AT THE TOP OF SOURCE FILES**__
-------------------------------
At the top of the source files, will be comments, explaining what that program does.
