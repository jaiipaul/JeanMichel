if(!'build'){
    mkdir build 
}
$env:CC="clang-cl.exe"
$env:CXX="clang-cl.exe"
cmake -G "NMake Makefiles" -S . -B .\build 



    