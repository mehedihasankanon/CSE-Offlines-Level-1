g++ -std=c++11 test.cpp arraystack.cpp liststack.cpp -o stack_test.exe

if ($?) {
    ./stack_test.exe
} else {
    Write-Error "Error: Compilation failed."
}

Read-Host -Prompt "Press Enter to exit"
