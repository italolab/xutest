
@echo off

set VERSION=1.0
set SO=windows
set ARCH=x64

set PROJ_NAME=xutest

set APP_FILE_NAME=%PROJ_NAME%
set LIB_FILE_NAME=lib%PROJ_NAME%.a

set BUILD_FOLDER=build
set APP_FOLDER=%PROJ_NAME%-%VERSION%-%SO%-%ARCH%

set APP_DIR=%BUILD_FOLDER%\%APP_FOLDER%

set APP_LIB_FILE=%APP_DIR%\%LIB_FILE_NAME%

rem LIMPANDO...

if exist %APP_DIR% (
    rmdir /s /q %APP_DIR%
    echo Removido: %APP_DIR%
)

if exist %APP_DIR%.zip (
    del %APP_DIR%.zip
    echo Removido: %APP_DIR%.zip
)

mkdir %APP_DIR%

rem COMPILANDO...

echo.
echo Compilando...
echo.

.\cbuild.exe archivebuildall --script=CBuildFile-StaticLib

rem COPIANDO HEADERS PARA A PASTA INCLUDE DO SOFTWARE EM BUILD

echo.
echo Copiando headers para pasta includes
mkdir %APP_DIR%\include
xcopy src\* %APP_DIR%\include /E /I /Ys

rem COPIANDO STATIC LIBRARY PARA PASTA LIB

echo.
echo Copiando static library para pasta lib
mkdir %APP_DIR%\lib
copy %APP_DIR%\libxutest.a %APP_DIR%\lib

rem EMPACOTANDO EM .ZIP

set CURR_DIR=%cd%

cd %BUILD_FOLDER%

echo.
echo Empacotando... %APP_DIR%.zip

tar acvf %APP_FOLDER%.zip %APP_FOLDER%
echo Finalizado.

cd %CURR_DIR%

rem BUILD CONCLUIDO

echo.
echo Build concluido!