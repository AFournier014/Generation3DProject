@echo off
setlocal

:: Emplacement standard de vcpkg sur le disque C:
set VCPKG_GLOBAL_DIR=C:\vcpkg
:: Dossier vcpkg local au projet
set VCPKG_LOCAL_DIR=%~dp0vcpkg

:: Vérification de l'existence de vcpkg dans l'emplacement global
if exist "%VCPKG_GLOBAL_DIR%\vcpkg.exe" (
    set VCPKG_DIR=%VCPKG_GLOBAL_DIR%
    echo Utilisation de vcpkg global trouvé à %VCPKG_DIR%.
) else (
    echo vcpkg n'est pas trouvé globalement à %VCPKG_GLOBAL_DIR%.
    :: Vérification de l'existence de vcpkg dans le dossier local du projet
    if not exist "%VCPKG_LOCAL_DIR%\vcpkg.exe" (
        echo Clonage de vcpkg dans le dossier local du projet...
        git clone https://github.com/microsoft/vcpkg "%VCPKG_LOCAL_DIR%"
        if errorlevel 1 (
            echo Erreur lors du clonage de vcpkg.
            exit /b 1
        )
        :: Initialisation de vcpkg
        call "%VCPKG_LOCAL_DIR%\bootstrap-vcpkg.bat"
        if errorlevel 1 (
            echo Erreur lors de l'initialisation de vcpkg.
            exit /b 1
        )
    ) else (
        echo Utilisation de vcpkg local trouvé dans le dossier du projet.
    )
    set VCPKG_DIR=%VCPKG_LOCAL_DIR%
)

:: Installation des dépendances via vcpkg
echo Installation des dépendances à partir de %VCPKG_DIR%...
call "%VCPKG_DIR%\vcpkg" install imgui glad --triplet x64-windows
if errorlevel 1 (
    echo Erreur lors de l'installation des dépendances.
    exit /b 1
)

echo Les dépendances ont été installées avec succès.
pause
