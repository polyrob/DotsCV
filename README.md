# DotsCV
C++ Dots mobile game solver using OpenCV.

![alt tag](http://i.imgur.com/K3oj1K9.png)

This was a personal challenge to learn a little about OpenCV and refresh my working knowledge in c++ (it's been a while). The goal is to determine the best move to make given the current board in [Dots](https://play.google.com/store/apps/details?id=com.nerdyoctopus.gamedots&hl=en). The program will access your webcam, scan your device's screen, determine which dots and what and where, construct a game board in memory, and then solve for all possible moves - returning the best move.

The goal is to get this to work for multiple iterations (as far as it can know given that it doesn't know what new dots will fall). It's a fun challenge and I was really glad to get something working.

Special thanks to Kyle Hounslow and his great [youtube series](https://www.youtube.com/watch?v=RS_uQGOQIdg) on tracking multiple objects with OpenCV - which help me get started quickly.
