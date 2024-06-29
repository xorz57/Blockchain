# Blockchain

![image](https://github.com/xorz57/Blockchain/assets/84932056/15f75242-1876-4dff-ac21-2289097d6ec6)
![image](https://github.com/xorz57/Blockchain/assets/84932056/6b030fcd-fa7a-4a11-a671-dc1d6ba0e1f3)
![image](https://github.com/xorz57/Blockchain/assets/84932056/04b8b9ab-0deb-4367-9a7f-6f00e50c28ff)

## Dependencies

- [openssl](https://github.com/openssl/openssl)
- [rapidjson](https://github.com/Tencent/rapidjson)

## How to Build

#### Linux & macOS

```bash
git clone https://github.com/microsoft/vcpkg.git ~/vcpkg
~/vcpkg/bootstrap-vcpkg.sh

git clone https://github.com/xorz57/Blockchain.git
cd Blockchain
cmake -B build -DCMAKE_BUILD_TYPE=Release -S . -DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release
ctest --build-config Release
```

#### Windows

```powershell
git clone https://github.com/microsoft/vcpkg.git C:/vcpkg
C:/vcpkg/bootstrap-vcpkg.bat
C:/vcpkg/vcpkg.exe integrate install

git clone https://github.com/xorz57/Blockchain.git
cd Blockchain
cmake -B build -DCMAKE_BUILD_TYPE=Release -S . -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release
ctest --build-config Release
```
