@echo off
setlocal

:: Chemin vers le répertoire racine de votre projet
set PROJECT_DIR=%~dp0

:: Chemin vers le dossier où vcpkg est installé
set VCPKG_DIR=%PROJECT_DIR%vcpkg

:: Vérifier si le répertoire de build existe, sinon le créer
if not exist "%PROJECT_DIR%build\" (
    mkdir "%PROJECT_DIR%build"
)

:: Configuration de CMake
cd "%PROJECT_DIR%build"
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_TOOLCHAIN_FILE=%VCPKG_DIR%\scripts\buildsystems\vcpkg.cmake

:: Compilation du projet
cmake --build . --config Release
cmake --build . --config Debug

echo Configuration et compilation terminees.
pause
