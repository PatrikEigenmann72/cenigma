 # ------------------------------------------------------------------------------------
# Script:       compile.ps1
# Description:  Compiles the source code.
#               This script does NOT install the project. Use install.ps1 for that.
# ------------------------------------------------------------------------------------
# Author:       Patrik Eigenmann
# email:        p.eigenmann72@gmail.com
# GitHub:       https://github.com/PatrikEigenmann72/Scripts
# ------------------------------------------------------------------------------------
# Change Log:
# Thu 2025-08-14 File created and content added.                        Version: 00.01
# Thu 2026-04-30 Updated to remove compilation logic.                   Version: 00.02
# Thu 2026-04-30 Added manpage-style help section.                      Version: 00.03
# ------------------------------------------------------------------------------------

param(
    [string]$Flag
)

function Show-Help {
@"
NAME
    compile.ps1 - compiles the project

SYNOPSIS
    .\compile.ps1 [OPTIONS]

DESCRIPTION
    This script takes the active directory as project name and
    installs the existing binary from .\bin\ into ~/bin.
    It does NOT compile the project. Use compile.ps1 first.

OPTIONS
    -h, -help, -?   Show this help menu

EXAMPLES
    .\compile.ps1
"@ | more
}

# Extract project name from current directory
$projectName = Split-Path -Leaf (Get-Location)
$binary = ".\bin\$projectName"

Write-Host "Compiling $projectName..."

gcc -Wall -Wextra -I./include -o $binary src/*.c