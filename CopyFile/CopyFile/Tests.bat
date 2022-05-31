@echo off

REM Путь к тестируемой программе передаётся через первый аргумент командной строки
SET MyProgram= "%~1"

REM ЗАщита от запуска без аргумента, задающего путь к программе
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Copy empty file
%MyProgram% Empty.txt "%TEMP%\output.txt" || goto err
fc Empty.txt "%TEMP%\output.txt" > nul || goto err
echo  Test 1 passed

REM Copy non empty file
%MyProgram% NonEmptyFile.txt "%TEMP%\output.txt" || goto err
fc NonEmptyFile.txt "%TEMP%\output.txt" > nul || goto err
echo  Test 2 passed

REM Copy missing file should fail
%MyProgram% MissingFile.txt "%TEMP%\output.txt" && goto err
echo  Test 3 passed

REM If output file is not srecified, program must fail
%MyProgram% NonEmptyFile.txt  && goto err
echo  Test 4 passed

REM If input and output file is not srecified, program must fail
%MyProgram%  && goto err
echo  Test 5 passed

REM Тесты прошли успешно
echo All tests passed successfuly
exit /B 0

REM Сюда будем попадать в случае ошибки
:err
echo Test failed
exit /B 1