@echo off
set number_of_turbines=%1

cd ..\CentralizedParkPilot

..\x64\Release\CentralizedParkPilot.exe -s -n %number_of_turbines%

exit