@call "C:\Users\salmas5\AppData\Roaming\MathWorks\MATLAB\R2011b\mexopts.bat"
@echo on
call "%VCINSTALLDIR%\vcvarsall.bat" x86_amd64
set MATLAB=C:\PROGRA~1\MATLAB\R2011b
nmake -f robot_demo.mk  GENERATE_REPORT=0 MAT_FILE=0 SHOW_TIMES=0 DEBUG=0 DEBUG_HEAP=0
