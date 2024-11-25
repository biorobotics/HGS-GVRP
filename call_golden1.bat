@echo off

setlocal enabledelayedexpansion

rem .exe location
set programma=.\Project1.exe

rem list of files where to read the data
set "files=Golden_1-C17-N241.gvrp	Golden_1-C18-N241.gvrp	Golden_1-C19-N241.gvrp	Golden_1-C21-N241.gvrp	Golden_1-C22-N241.gvrp	Golden_1-C25-N241.gvrp	Golden_1-C27-N241.gvrp	Golden_1-C31-N241.gvrp	Golden_1-C35-N241.gvrp	Golden_1-C41-N241.gvrp	Golden_1-C49-N241.gvrp																																																																																								
"
rem Loop through the files
> log1.txt (
   for %%f in (%files%) do (
      echo %%f
         set "output_file=.\sol_%%~nxf"
         set "input_file=Problems\Golden\%%~nxf"
         call %programma% !input_file! !output_file!  -t 10 -log 0 -cluvrp 1
   )
)
endlocal
