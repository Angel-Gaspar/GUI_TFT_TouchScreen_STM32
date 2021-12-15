# Welcome to GitHub Desktop!

This is your README. READMEs are where you can communicate what your project is and how to use it.

Write your name on line 6, save it, and then head back to GitHub Desktop.
Angel Gaspar Gonzalez Rodriguez
GUI_TFT_TouchScreen_STM32

This is a GUI for a touch TFT 3.5'' screen (480x320) with SPI to be driven with a STM32 altough can be adapted to any other microcontroller. The application is a squash scoreboard but it can be used as a TEMPLATE for your own designs.

It can be opened from two sources (in fact it consists of two projects): one for a STM32, and one to be opened in a desktop IDE.

The FINAL aim is to be opened with a STM32 IDE (I used STM32CubeIDE 1.7.0). However, debugging the code is slow and requires the connection of the hardware.

This is because I created a previous project to be opened with Visual Studio 2010 or similar that manages Win32 projects in C++. It is used to develop 95% of the GUI and its functionalities. It is faster and does not require connecting any hardware. Once it is tested in your PC/laptop, you can complete your project with your microcontroller IDE.

The source files inside SRC_TFT are necessary to drive a touch screen TFT 3.5'' 480x320 with SPI, including the IC 9488.
The source files inside SRC_GUI are necessary to use the components (buttons, textboxes... ) for the graphical interface GUI.
The source files inside SRC_INC_myApp are related to my application (a squash scoreboard) and can be used as a template for your design.
The source files inside Graph_Win32_GUI are wrapper files related to my applications. This folder must be disregarded when using a microcontroller IDE. These files must be included in a Win32 project for your desktop IDE (e.g. VS2010). Please exclude prWin32.cpp, but use it as a template as the main file. If your project name is myProject, then  you should copy the lines of prWin32.cpp inside your myProject.cpp and substitute the following strings: prWin32 by myProject    and     PRWIN32 by MYPROJECT
The header files inside INC_TFT_GUI are all of the include files. Sorry for grouping all of them. This way is faster to include the folder in a IDE.

You can find a demo of how you can test this gui in youtube https://www.youtube.com/watch?v=fyzccLtsbPg altough in this new version: it is not necessary to add defines to your project; and the subfolders inside SRC_TFT and inside INC_TFT_GUI have been also removed.

