@echo off

REM Путь к тестируемой программе передаётся через первый аргумент командной строки
SET MyProgram= "%~1"

REM Защита от запуска без аргумента, задающего путь к программе
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Find in empty file
 %MyProgram% Empty.txt "a" && goto err
 echo  Test 1 passed

REM Copy non empty file
 %MyProgram% input.txt "pa" || goto err
 echo  Test 2 passed

 REM Run with more arguments
 %MyProgram% Empty.txt "a" 1 "d" && goto err
 echo  Test 3 passed

 REM Run with no arguments
 %MyProgram%  && goto err
 echo  Test 4 passed


REM Тесты прошли успешно
echo All tests passed successfuly
exit /B 0

REM Сюда будем попадать в случае ошибки
:err
echo Test failed
exit /B 1