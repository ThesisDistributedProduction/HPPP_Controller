
@echo off
set N_INSTANCES=%1
set START_ID=%2

IF "%START_ID%"=="" set START_ID=1

cd HPPP_Controller

:Loop
IF "%N_INSTANCES%"=="0" GOTO Continue
	set /a id=%START_ID%+%N_INSTANCES%
	echo Starting: %id%
	start ..\x64\Release\HPPP_Controller.exe %id%

	set /a N_INSTANCES=%N_INSTANCES%-1
GOTO Loop
:Continue

cd ..

echo Press any key to kill all processes
pause 

taskkill /F /IM HPPP_Controller.exe /T