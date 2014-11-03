
@echo off
set N_INSTANCES=%1

cd HPPP_Controller

:Loop
IF "%N_INSTANCES%"=="0" GOTO Continue

	echo Starting: %N_INSTANCES%
	start ..\x64\Release\HPPP_Controller.exe

set /a N_INSTANCES=%N_INSTANCES%-1
SHIFT
GOTO Loop
:Continue

cd ..

echo Press any key to kill all processes
pause 

taskkill /F /IM HPPP_Controller.exe /T