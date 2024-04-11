@echo off
setlocal

:: Définir le chemin local par défaut de vcpkg par rapport à l'emplacement du script
set VCPKG_LOCAL_DIR=%~dp0vcpkg

:: Utiliser VCPKG_ROOT si défini, sinon utiliser le chemin local
if defined VCPKG_ROOT (
    set VCPKG_DIR=%VCPKG_ROOT%
) else (
    set VCPKG_DIR=%VCPKG_LOCAL_DIR%
)

:: Vérification de l'existence de vcpkg dans le dossier local du projet
if not exist "%VCPKG_DIR%\vcpkg.exe" (
    echo Clonage de vcpkg dans le dossier local du projet...
    git clone https://github.com/microsoft/vcpkg "%VCPKG_DIR%"
	
    :: Initialisation de vcpkg
    call "%VCPKG_DIR%\bootstrap-vcpkg.bat"

) else (
	echo Utilisation de vcpkg local trouve dans le dossier du projet.
)

:: Installation des dépendances via vcpkg
echo Installation des dependances a partir de %VCPKG_DIR%...
call "%VCPKG_DIR%\vcpkg" install

:: Intégration de vcpkg avec Visual Studio
echo Integration de vcpkg avec Visual Studio...
call "%VCPKG_DIR%\vcpkg" integrate install

echo Les dependances ont ete installees avec succes.

call "%~dp0cmake-build.bat"

pause
