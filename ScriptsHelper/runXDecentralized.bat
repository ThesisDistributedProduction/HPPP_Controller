
@echo off
set N_INSTANCES=%1
set START_ID=%2

IF "%START_ID%"=="" set START_ID=0

:Loop
IF "%N_INSTANCES%"=="0" GOTO Continue
	set /a id=%START_ID%+%N_INSTANCES%
	start /B runDecentralized.bat

	set /a N_INSTANCES=%N_INSTANCES%-1
GOTO Loop
:Continue

sleep 2
echo Press any key to kill all processes
pause 

taskkill /F /IM DecentralizedParkPilot.exe /T