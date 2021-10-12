@echo off

cd /D "%~dp0"

IF exist "P:\SP_Menu\" (
	echo Removing existing link P:\SP_Menu
	rmdir "P:\SP_Menu\"
)

echo Creating link P:\SP_Menu
mklink /J "P:\SP_Menu\" "%cd%\SP_Menu\"

echo Done