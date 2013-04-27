@echo off
REM ====================================
REM Tool to update the Libraries archive
REM ====================================

REM Chemin vers votre dossier WinRAR
set rar_path="C:\Program Files\WinRAR"

REM Chemin vers le dossier de sortie du zip
set output_path=".."

REM Nom du dossier à ziper
set folder=Libraries

IF EXIST %output_path%\%folder%.zip (
	echo Archive %folder%.zip already exists, deleting it ...
	del %output_path%\%folder%.zip
	echo Archive %folder%.zip deleted !
	)
echo Archiving the %folder% folder ...
%rar_path%\rar a -m5 %output_path%\%folder%.zip ..\%folder%
REM Permet d'attendre X secondes avant de continuer
ping -n 2 127.0.0.1 >nul