Get-ChildItem -Path . -Filter *.gcda -Recurse -File -Name| ForEach-Object {
    Write-Host $_
    start-process C:\msys64\mingw64.exe -ArgumentList "gcov $_ -p" -NoNewWindow -Wait
}

New-Item -Path ".\.." -Name "Gcov" -ItemType "directory"

Get-ChildItem -Path ".\*.gcov" -Recurse | Move-Item -Destination ".\..\Gcov"