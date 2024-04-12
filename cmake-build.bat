@echo off
setlocal

cmake --version
if %ERRORLEVEL% equ 1 (
    echo CMake is already installed.
) else (
	echo Installing CMake...
	powershell -Command "& {$url = 'https://github.com/Kitware/CMake/releases/download/v3.29.2/cmake-3.29.2-windows-x86_64.msi'; $output = 'cmake_installer.msi'; Invoke-WebRequest -Uri $url -OutFile $output; Start-Process msiexec.exe -ArgumentList '/i', $output, '/quiet', '/norestart' -Wait; Remove-Item -Force $output;}"
	if %ERRORLEVEL% neq 0 (
		echo Failed to install CMake.
		exit /b 1
	)
	echo CMake installed successfully.
)

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