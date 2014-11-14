@echo off

cd CentralizedParkPilot

REM ..\x64\Release\CentralizedParkPilot.exe %number_of_turbines% > nul 2>&1
..\x64\Release\CentralizedParkPilot.exe %number_of_turbines%

exit