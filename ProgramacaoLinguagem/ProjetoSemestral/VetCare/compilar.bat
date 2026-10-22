@echo off

gcc -Wall -Wextra *.c -o C:\VetCare\Aplicativo\VetCare.exe

if errorlevel 1 (
    echo.
    echo ERRO NA COMPILACAO!
    exit /b 1
)

echo.
echo Compilacao concluida com sucesso!