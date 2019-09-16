![Build Status](https://travis-ci.com/gupta409/Floorplanner.svg?branch=master)
------------------------------------------------------------------------------------
SIMULATED ANNEALING BASED FLOORPLANNER
------------------------------------------------------------------------------------
'''text
___________.__                             .__                                     
\_   _____/|  |   ____   _________________ |  | _____    ____   ____   ___________ 
 |    __)  |  |  /  _ \ /  _ \_  __ \____ \|  | \__  \  /    \ /    \_/ __ \_  __ \
 |     \   |  |_(  <_> |  <_> )  | \/  |_> >  |__/ __ \|   |  \   |  \  ___/|  | \/
 \___  /   |____/\____/ \____/|__|  |   __/|____(____  /___|  /___|  /\___  >__|   
     \/                             |__|             \/     \/     \/     \/       
'''text
------------------------------------------------------------------------------------
Folder Structure
------------------------------------------------------------------------------------
'''text
Root:
	Code:
		Makefile
		constants.cfg                          
		main.cpp  
		Floorplanner.cpp		
		Node.cpp               
		Size.cpp
		FloorplannerConstants.cpp
		IOUtilites.cpp
		PolishUtilities.cpp
		RandomizeUtilites.cpp
		IOUtilites_test.cpp
		PolishUtilites_test.cpp
		FloorplannerConstants_test.cpp                  
		RandomizeUtilites_test.cpp
		Node_test.cpp                             
		Floorplanner_test.cpp           
		PolishUtilities.hpp
		IOUtilites.hpp
		FloorplannerConstants.hpp
		PolishUtilities.hpp
		RandomizeUtilites.hpp
		Size.hpp
		Node.hpp
		Floorplanner.hpp     
	Documentation:
		Analysis of Simulated Annealing.pdf	                        
	TestFolder:
		n10hard:
			n10hard.blocks
			parser
		n30hard
		......
		......
		n300soft
'''text
------------------------------------------------------------------------------------
How to Run
------------------------------------------------------------------------------------
1. Generate executable for floorplanner
	a. Goto Code/
	b. run 'make' command in terminal
2. Using the executable
	a. Run the execuatble in folder containing the input file (say n100hard.blocks)
	b. Optional: Constants.cfg can also be kept in the same file to override constants. If file is not found in the same folder program uses default constants.
	c. On running the file the programs asks for the input file name, enter the fill name here including the extention. Eg: n100hard.blocks 
	d. The entry is case sensitive.
3. Wait until simulation is completed.
4. Files generated:
	a. <InputFileName>.out: This file contatins required output in the required foramt, ie. co-ordinates and area data.
	b. stats.txt: This file contains two values: Runtime, Percent of Black Area in the output.
	c. <InputFileName>dump.csv: This is a csv file with all the data about Temperature, Cost, Moves and Delta Cost at each iteration. This file can be used for analysis of simulated annealing performed
------------------------------------------------------------------------------------
Details of Individual "Code" Files
------------------------------------------------------------------------------------
Makefile:			This file is the main file being used for compiling and creating the executable of the program.
constants.cfg:	 	This is an optional input file to the program. It is used to override default constants.
main.cpp:			C++ 11 file with the main call
Floorplanner.cpp:	Floorplanner class responsible for performing all floorplan related operations
Node.cpp:			Base entity class for storing the Node(Block) related properties as well as methods
Size.cpp:			Base entity class to store size information (length X width)
FloorplannerConstants.cpp: Class providing all simulated annealing constants to the floorplanner
IOUtilities.cpp:		Utility class for all IO operations
PolishUtilities.cpp:	Utility class for all Polish Expression Related functions
RandomizeUtilities.cpp:	Utility class for all random number generator and distributor related operations
<Name>_test.cpp:	Various C++ files to test individual classes and their operations.
<Name>.hpp:			Header files for relavent classes.
------------------------------------------------------------------------------------
Details of TestFolder
------------------------------------------------------------------------------------
Contains readymade execuatble to and benchmark files to benchmark the program by running 100 times and giving average runtime and average % black area.
All output data is stored in same folders as listed above.
HOW TO USE:
Simply call ./parser
No requirement of giving indidual file name
Working can be overriden by use of constraints.cfg file as listed above.

