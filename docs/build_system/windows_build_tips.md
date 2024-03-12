# Windows 平台编译 Open RV 踩坑记录

WindowsUIModify 分支信息：
- 该分支仅根据本人编译时遇到的问题修改了部分 cmake 代码以及 C++ 依赖，不会卡死在项目配置；
- Python 版本从官方的 3.10.13 调整为 3.10.12，与 MSYS2 一致；
- PySide2 版本从官方的 5.15.10 调整为 5.15.13；
- 取消 FFMEPG 的 AV1 编码支持；
- 启用 H.264、AAC 等 Open RV 默认不支持的商用编解码器；
- 调整了 Session Manager 界面布局和整体 Stylesheet，使界面扁平化；


## 1. 按照官方文档进行环境配置
- 安装 Microsoft Visual Studio，我自己使用的是 2019。
- 安装 Qt，注意安装版本需要与 Visual Studio 一致, VS2019 对应 msvc2019_64，QtWebEngine 相关的模块都需要勾选。
- 安装 Strawberry Perl，没啥需要注意的。
- 安装 MSYS2， 装完需要配置环境变量，把 MSYS2 的 bin 路径调整到 Strawberry Perl 之前。
- 安装 MSYS2 的编译依赖包，其中可以先不安装 meson， python-pip 和 python-psutil，因为 Open RV 的 Python 版本为 3.10.13，MSYS2 使用 pacman 默认安装的 Python 为 3.11.8（2024年3月，之后版本会更高），会导致后续发生 Python 版本不同而导致编译失败。
- 拉取 ASWF/OpenTimelineIO 源码，后续 CMake 配置时会自动拉取，但受网络环境影响可能无法顺利拉取，所以可以先手动操作后设置。


## 2. 在 MSYS2 中安装 Python 3.10.12 及相关依赖
运行 MSYS2 MINGW64，安装 Python 3.10.12 及 pip，psutil，ninja 和 clang。

```shell
pacman -U https://repo.msys2.org/mingw/mingw64/mingw-w64-x86_64-python-3.10.12-1-any.pkg.tar.zst
pacman -U https://repo.msys2.org/mingw/mingw64/mingw-w64-x86_64-python-pip-23.1-1-any.pkg.tar.zst
pacman -U https://repo.msys2.org/mingw/mingw64/mingw-w64-x86_64-python-psutil-5.9.0-1-any.pkg.tar.zst
pacman -Sy --needed meson ninja clang
```

## 3. 在 MSYS2 中安装编译PySide2 时需要的 py7zr
运行 MSYS2 MINGW64，设置环境变量后安装编译 py7zr。

```shell
export SETUPTOOLS_USE_DISTUTILS=stdlib
python3 -m pip install py7zr
```

## 4. 通过 CMake GUI 配置项目
本机安装的 CMake 为 3.28.3，如果有 CMake 基础可以直接命令行配置。

- 指定 source 目录和 build 目录。
- 点击 Configure，Specify the generator for this project 选择安装的 Visual Studio 16 2019。
- 下方选择 Specify native compilers，点击 Next。
- Compilers 中 C 和 Fortan 留空，C++ 指定 MSYS2 安装的 ninja：C:/msys64/mingw64/bin/ninja.exe，点击 Finish。
- CMAKE_INSTALL_PREFIX 设置为自己需要的路径，避免默认 C:/Program Files (x86)/open-rv 无权限写入。
- RV_DEPS_QT5_LOCATION：C:/Qt/5.15.2/msvc2019_64
- RV_DEPS_WIN_PERL_ROOT：C:/Strawberry/perl/bin
- FTECHCONTENT_SOURCE_DIR_RV_DEPS_OPENTIMELINEIO：如果 OpenTimelineIO 源码拉取失败，设置成之前拉取的路径

完成 CMake 配置后打开项目

## 5. Visual Studio 编译
其中 RV_DEPS 开头的项目需要下载源码包，可以优先生成。如果下载失败，可以根据生成信息找到下载路径和保存路径，手动下载改名后放在 {生成目录}/RV_DEPS_DOWNLOAD 下再次生成。

1. 生成 RV_DEPS_VCPKG：需要拉取 VCPKG，容易失败，建议先生成；
2. 生成 RV_DEPS_OIIO：先生成一次，等依赖项目都编译完后会提示无法找到 Boost 相关依赖。
3. 编辑 {生成目录}/RV_DEPS_OIIO/build/CMakeCache.txt，手动设置未找到的 boost 依赖的 lib 文件路径
   ```shell
   //Boost atomic library (release)
   Boost_ATOMIC_LIBRARY_RELEASE:FILEPATH={生成目录}/RV_DEPS_BOOST/install/lib/boost_atomic-vc143-mt-x64-1_80.lib

   //Boost chrono library (release)
   Boost_CHRONO_LIBRARY_RELEASE:FILEPATH={生成目录}/RV_DEPS_BOOST/install/lib/boost_chrono-vc143-mt-x64-1_80.lib

   //Boost filesystem library (release)
   Boost_FILESYSTEM_LIBRARY_RELEASE:FILEPATH={生成目录}/RV_DEPS_BOOST/install/lib/boost_filesystem-vc143-mt-x64-1_80.lib

   //Boost thread library (release)
   Boost_THREAD_LIBRARY_RELEASE:FILEPATH={生成目录}/RV_DEPS_BOOST/install/lib/boost_thread-vc143-mt-x64-1_80.lib
   ```

4. 编辑 clang-format.exe 路径，clang-format.exe 为 C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/Llvm/x64/bin/clang-format.exe， 路径无需添加引号。
   ```shell
   //Path to clang-format executable
   CLANG_FORMAT_EXE:FILEPATH=C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/Llvm/x64/bin/clang-format.exe
   ```

5. 再次生成 RV_DEPS_OIIO （暂时无法找到更优的解决方法，只能手动修改 cmake 的缓存文件。）。
6. 最后生成 INSTALL 项目，完成 Open RV 的编译。