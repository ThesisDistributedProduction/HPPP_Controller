@echo off

cd ..\TurbineForCentralizedParkPilot

REM ..\x64\Release\TurbineForCentralizedParkPilot.exe %id% > nul 2>&1
..\x64\Release\TurbineForCentralizedParkPilot.exe -id %id% -s -msleep 0
exit