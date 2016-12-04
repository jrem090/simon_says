#John Says
#Description

The application built by this code is a game similair to the old Simon handheld game.
The code is written in c++ using Qt Libraries

#How to Build
##Windows
This was developed using MinGW compiler in QtCreator. I would reccommend
using the QtCreator IDE and using the opening the sudoku solver project
file. Then using the the native build command in Qt Creator for a
dynamic build.

To build a static version add the "-config static" flag to the arguments 
in qmake. Also make a custom process that calls windeployqt.exe and
specifies the build directory as an arguement.
##MAC
*Not attempted yet*
##Linux
*Not attempted yet*

#Future Devolopments

-Add an expert mode which uses a new sequence evry succesful run
