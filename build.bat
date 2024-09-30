if not exist build mkdir build
cd build
cmake -S ../ -B . -G "MinGW Makefiles"
mingw32-make.exe
move opencv_webcam_test.exe ../
cd ..
pause