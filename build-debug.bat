@echo off

echo /============ PREPARE =============
echo /

xcopy .\amxmodx\scripting\include C:\AmxModX\1.9.0\include /s /e /y
xcopy .\amxmodx\scripting\include C:\AmxModX\1.10.0\include /s /e /y

mkdir .\.build\VotingSystem\amxmodx\configs

if exist .\amxmodx\plugins rd /S /q .\amxmodx\plugins
mkdir .\amxmodx\plugins
cd .\amxmodx\plugins

set PLUGINS_LIST=..\..\.build\VotingSystem\amxmodx\configs\plugins-VotingSystem.ini
echo. 2>%PLUGINS_LIST%

echo /
echo /
echo /============ COMPILE =============
echo /

for /R ..\scripting\ %%F in (*.sma) do (
    echo / /
    echo / / Compile %%~nF:
    echo / /
    amxx1100 DEBUG=1 %%F
    echo %%~nF.amxx debug>>%PLUGINS_LIST%
)

echo /
echo /
echo /============ BUILD =============
echo /

cd ..\..

xcopy .\amxmodx\ .\.build\VotingSystem\amxmodx\ /s /e /y

if exist .\VotingSystem-debug.zip del .\VotingSystem-debug.zip
cd .\.build
zip -r .\..\VotingSystem-debug.zip .
cd ..
rmdir .\.build /s /q

echo /
echo /
echo /============ END =============
echo /

set /p q=