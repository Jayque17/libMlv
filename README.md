# libMLV

## How to build

Run ./build.sh. The archive libMlv-1.1-build.tar will be created and contain include files and archive to link to.

## How to use

Extract libMlv-1.1-build.tar in your project and use (assuming all your source files are in `src/` folder):

```bash
gcc -o executable_name src/*.c -I libMlv-1.1-build/include -L libMlv-1.1-build/lib -lMlv -lX11
```