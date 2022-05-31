@echo off

REM Путь к тестируемой программе передаётся через первый аргумент командной строки
SET MyProgram= "%~1"

REM Защита от запуска без аргумента, задающего путь к программе
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Запуск программы с обычной задачей(основания в пределах 10-ти)
cd.>"%TEMP%\output.txt"
%MyProgram% 2 4 101011 >> "%TEMP%\output.txt" || goto err
fc output1.txt "%TEMP%\output.txt" > nul || goto err
echo  Test 1 passed

REM Запуск без аргументов
 %MyProgram%  && goto err
 echo  Test 2 passed

REM Некорректный ввод(основание не соотносится с числом)
cd.>"%TEMP%\output.txt"
%MyProgram% 16 10 G >> "%TEMP%\output.txt" && goto err
fc output3.txt "%TEMP%\output.txt" > nul || goto err
echo  Test 3 passed

REM Некорректный ввод(неправильное основание)
cd.>"%TEMP%\output.txt"
%MyProgram% -1 40 G >> "%TEMP%\output.txt" && goto err
fc output4.txt "%TEMP%\output.txt" > nul || goto err
echo  Test 4 passed

REM MaxInt
cd.>"%TEMP%\output.txt"
%MyProgram% 10 16 2147483647 >> "%TEMP%\output.txt" || goto err
fc output5.txt "%TEMP%\output.txt" > nul || goto err
echo  Test 5 passed

REM MaxInt+1
cd.>"%TEMP%\output.txt"
%MyProgram% 10 16 2147483648 >> "%TEMP%\output.txt" && goto err
fc output6.txt "%TEMP%\output.txt" > nul || goto err
echo  Test 6 passed

REM Перевод из максимальной системы счисления
cd.>"%TEMP%\output.txt"
%MyProgram% 36 10 Z6 >> "%TEMP%\output.txt" || goto err
fc output7.txt "%TEMP%\output.txt" > nul || goto err
echo  Test 7 passed

REM Перевод числа 0
cd.>"%TEMP%\output.txt"
%MyProgram% 2 10 0 >> "%TEMP%\output.txt" || goto err
fc output8.txt "%TEMP%\output.txt" > nul || goto err
echo  Test 8 passed

REM Перевод минимального числа
cd.>"%TEMP%\output.txt"
%MyProgram% 10 2 1 >> "%TEMP%\output.txt" || goto err
fc output9.txt "%TEMP%\output.txt" > nul || goto err
echo  Test 9 passed

REM MinInt
cd.>"%TEMP%\output.txt"
%MyProgram% 10 16 -2147483647 >> "%TEMP%\output.txt" || goto err
fc output10.txt "%TEMP%\output.txt" > nul || goto err
echo  Test 10 passed

REM MinInt-1
cd.>"%TEMP%\output.txt"
%MyProgram% 10 16 -2147483648 >> "%TEMP%\output.txt" && goto err
fc output6.txt "%TEMP%\output.txt" > nul || goto err
echo  Test 11 passed

REM Тесты прошли успешно
echo All tests passed successfuly
exit /B 0

REM Сюда будем попадать в случае ошибки
:err
echo Test failed
exit /B 1