# Welcome to GitHub Desktop!

This is your README. READMEs are where you can communicate what your project is and how to use it.

Write your name on line 6, save it, and then head back to GitHub Desktop.
Angel Gaspar Gonzalez Rodriguez
GUI_TFT_TouchScreen_STM32

This is a GUI for a touch TFT 3.5'' screen (480x320) with SPI to be driven with a STM32 altough can be adapted to any other microcontroller. It can be opened from two sources (in fact it consists of two projects):

The FINAL aim is to be opened with a STM32 IDE (I used STM32CubeIDE 1.7.0). However, debugging the code is slow and requires the connection of the hardware. Codified in C.
The FIRST project must be opened with Visual Studio 2010 or similar that manages Win32 projects in C++; it is used to develop 95% of the GUI and its functionalities. It is faster and does not require connecting any hardware. Once it is tested in your PC/laptop, you can complete your project with your microcontroller IDE.
