@echo off

REM Путь к тестируемой программе передаётся через первый аргумент командной строки
SET MyProgram= "%~1"

REM Защита от запуска без аргумента, задающего путь к программе
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Запуск программы с обычной задачей
cd.>"%TEMP%\output.txt"
%MyProgram% input1.txt "%TEMP%\output.txt" || goto err
fc output1.txt "%TEMP%\output.txt" > nul || goto err
echo  Test 1 passed

REM Запуск без аргументов
 %MyProgram%  && goto err
 echo  Test 2 passed

REM Проверка на переполнение стека
cd.>"%TEMP%\output.txt"
%MyProgram% input2.txt "%TEMP%\output.txt" || goto err
fc output2.txt "%TEMP%\output.txt" > nul || goto err
echo  Test 3 passed

REM Некорректный ввод(символ)
cd.>"%TEMP%\output.txt"
%MyProgram% input3.txt "%TEMP%\output.txt" && goto err
fc output3.txt "%TEMP%\output.txt" > nul || goto err
echo  Test 4 passed

REM Проверка на игнорирование символов во входном файле вне квадрата 100Х100
cd.>"%TEMP%\output.txt"
%MyProgram% input4.txt "%TEMP%\output.txt" || goto err
fc output4.txt "%TEMP%\output.txt" > nul || goto err
echo  Test 5 passed

REM Проверка на распространение по диагонали
cd.>"%TEMP%\output.txt"
%MyProgram% input5.txt "%TEMP%\output.txt" || goto err
fc output5.txt "%TEMP%\output.txt" > nul || goto err
echo  Test 6 passed

REM Проверка на наличие двух начальных точек в одном контуре
cd.>"%TEMP%\output.txt"
%MyProgram% input6.txt "%TEMP%\output.txt" || goto err
fc output6.txt "%TEMP%\output.txt" > nul || goto err
echo  Test 7 passed

REM Проверка на "проливание" из контура
cd.>"%TEMP%\output.txt"
%MyProgram% input7.txt "%TEMP%\output.txt" || goto err
fc output7.txt "%TEMP%\output.txt" > nul || goto err
echo  Test 8 passed

REM Тесты прошли успешно
echo All tests passed successfuly
exit /B 0

REM Сюда будем попадать в случае ошибки
:err
echo Test failed
exit /B 1