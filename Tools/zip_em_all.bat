@echo off
REM =============================
REM Tool tool update the archives
REM =============================

call zip-Libraries.bat
echo Archive 1/2 complete !
echo Archive 2/2 starting ...
call zip-Media.bat
echo Archive 2/2 complete !
pause