@echo off

cd ..\DecentralizedParkPilot

echo Starting: %id%

..\x64\Release\DecentralizedParkPilot.exe -id %id% -s

exit