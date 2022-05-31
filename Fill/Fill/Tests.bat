@echo off

REM ���� � ����������� ��������� ��������� ����� ������ �������� ��������� ������
SET MyProgram= "%~1"

REM ������ �� ������� ��� ���������, ��������� ���� � ���������
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM ������ ��������� � ������� �������
cd.>"%TEMP%\output.txt"
%MyProgram% input1.txt "%TEMP%\output.txt" || goto err
fc output1.txt "%TEMP%\output.txt" > nul || goto err
echo  Test 1 passed

REM ������ ��� ����������
 %MyProgram%  && goto err
 echo  Test 2 passed

REM �������� �� ������������ �����
cd.>"%TEMP%\output.txt"
%MyProgram% input2.txt "%TEMP%\output.txt" || goto err
fc output2.txt "%TEMP%\output.txt" > nul || goto err
echo  Test 3 passed

REM ������������ ����(������)
cd.>"%TEMP%\output.txt"
%MyProgram% input3.txt "%TEMP%\output.txt" && goto err
fc output3.txt "%TEMP%\output.txt" > nul || goto err
echo  Test 4 passed

REM �������� �� ������������� �������� �� ������� ����� ��� �������� 100�100
cd.>"%TEMP%\output.txt"
%MyProgram% input4.txt "%TEMP%\output.txt" || goto err
fc output4.txt "%TEMP%\output.txt" > nul || goto err
echo  Test 5 passed

REM �������� �� ��������������� �� ���������
cd.>"%TEMP%\output.txt"
%MyProgram% input5.txt "%TEMP%\output.txt" || goto err
fc output5.txt "%TEMP%\output.txt" > nul || goto err
echo  Test 6 passed

REM �������� �� ������� ���� ��������� ����� � ����� �������
cd.>"%TEMP%\output.txt"
%MyProgram% input6.txt "%TEMP%\output.txt" || goto err
fc output6.txt "%TEMP%\output.txt" > nul || goto err
echo  Test 7 passed

REM �������� �� "����������" �� �������
cd.>"%TEMP%\output.txt"
%MyProgram% input7.txt "%TEMP%\output.txt" || goto err
fc output7.txt "%TEMP%\output.txt" > nul || goto err
echo  Test 8 passed

REM ����� ������ �������
echo All tests passed successfuly
exit /B 0

REM ���� ����� �������� � ������ ������
:err
echo Test failed
exit /B 1