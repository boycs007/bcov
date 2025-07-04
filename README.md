# bcov

`bcov` 是一个用于 C++ 子进程覆盖率收集的小型库。它通过在子进程启动时调用 `InitChildCoverage()`，并在收到 `SIGTERM` (kill -15) 信号时自动生成覆盖率数据。

## 安装与集成

### 方式一：标准 CMake 安装 + find_package

1. **安装 bcov 到本地目录**
    ```sh
    cmake -S . -B build -DCMAKE_INSTALL_PREFIX=/your/install/path
    cmake --build build
    cmake --install build
    ```

2. **用户工程 CMakeLists.txt 示例**
    ```cmake
    find_package(bcov REQUIRED PATHS /your/install/path/lib/cmake/bcov)

    add_executable(user_app main.cpp)
    target_link_libraries(user_app PRIVATE bcov::bcov)
    ```
    头文件会自动可用，无需手动设置 include 路径。

---

## 推荐集成方式（源码拉取）

建议通过 [FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html) 拉取本库，并用编译宏控制是否启用覆盖率收集。

### 用户侧 CMakeLists.txt 示例

```cmake
if(BUILD_WITH_COVERAGE)
    add_compile_definitions(-DTCOVERAGE)
    FetchContent_Declare(bcov
        GIT_REPOSITORY    https://github.com/boycs007/bcov.git
        GIT_TAG           master
    )
    FetchContent_MakeAvailable(bcov)

    target_compile_options(${PROJECT_NAME} PRIVATE -O0 -coverage)
    target_link_options(${PROJECT_NAME} PRIVATE -coverage -static)
    target_link_libraries(${PROJECT_NAME} PRIVATE bcov)
endif()
```

### 用户侧代码示例

```cpp
#ifdef TCOVERAGE
#include "bcov.h"
#endif

// other codes

#ifdef TCOVERAGE
// 尽早启动
    InitChildCoverage();
#endif
```

## bcov 库自身 CMake

本库仅导出静态库和头文件，不自动添加 `-coverage` 等编译/链接选项，需用户在主工程自行设置。

## 覆盖率数据生成

当你用 `kill -15 <pid>` 结束子进程时，会在如下目录生成覆盖率数据：
- 默认目录：`/data/coverage_data/cov_<pid>`
- 可通过环境变量 `GCOV_PREFIX_CHILD` 指定根目录

## 注意事项
- 需要编译时加上 `-coverage` 以启用 gcov 支持（主工程 CMake 设置）
- 需确保链接时包含 `gcov` 库（通常 `-coverage` 会自动处理）

## License
MIT
