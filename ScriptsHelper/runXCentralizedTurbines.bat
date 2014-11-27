
@echo off
set N_INSTANCES=%1
set START_ID=%2

IF "%START_ID%"=="" set START_ID=0
IF "%N_INSTANCES%"=="" set N_INSTANCES=1

:Loop
IF "%N_INSTANCES%"=="0" GOTO Continue
	set /a id=%START_ID%+%N_INSTANCES%
	echo Starting: %id%
	start runCentralizedTurbine.bat
	
	set /a N_INSTANCES=%N_INSTANCES%-1
GOTO Loop
:Continue

echo Press any key to kill all processes
pause 

taskkill /F /IM CentralizedParkPilot.exe /T
taskkill /F /IM TurbineForCentralizedParkPilot.exe /T