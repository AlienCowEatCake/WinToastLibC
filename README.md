# WinToastLibC
**WinToastLibC** is a C bindings for [WinToast library](https://github.com/mohabouje/WinToast). With this bindings you can use the modern toast notifications of Windows 8 & Windows 10 in projects written in C or compiled with non-MSVC compilers.

## Documentation
Since this project is just bindings, documentation can be found in [WinToast](https://github.com/mohabouje/WinToast) project.

## Examples
* [example1.c](example/example1.c): minimal C code to show the toast notification
* [example2.c](example/example2.c): more complex example with image and basic AUMID registration

## MinGW integration

### Build as is
```bash
gcc example1.c wintoastlibc.lib -lole32 -mwindows
```

### Build with fake implib
```bash
mv wintoastlibc.lib libwintoastlibc.dll.a
gcc example1.c -L. -lwintoastlibc -lole32 -mwindows
```

### Build with true implib
```bash
gendef wintoastlibc.dll
dlltool.exe -d wintoastlibc.def -D wintoastlibc.dll -l libwintoastlibc.dll.a
gcc example1.c -L. -lwintoastlibc -lole32 -mwindows
```

### Build with delayed loader (dll)
Loader source: [wintoastlibc_lazy.c](src/wintoastlibc_lazy.c)
```bash
gcc -shared -o wintoastlibc_lazy.dll \
    -Wl,--out-implib=libwintoastlibc.dll.a \
    -Wl,--export-all-symbols -Wl,--enable-auto-import \
    -Wl,--whole-archive wintoastlibc_lazy.c -Wl,--no-whole-archive
gcc example1.c -L. -lwintoastlibc -lole32 -mwindows
```

### Build with delayed loader (static)
Loader source: [wintoastlibc_lazy.c](src/wintoastlibc_lazy.c)
```bash
gcc -DWTLC_BUILD_STATIC -o wintoastlibc_lazy.o -c wintoastlibc_lazy.c
ar rcs libwintoastlibc.dll.a wintoastlibc_lazy.o
gcc example1.c -DWTLC_BUILD_STATIC -L. -lwintoastlibc -lole32 -mwindows
```

## Links
* https://github.com/mohabouje/WinToast
