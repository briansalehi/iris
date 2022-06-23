# Adjust Brightness

Command line tool to adjust your screen's brightness.

**NOTE:** This tool only works on Linux systems.

## Setup

There are three implementations of this project: Bash, C and C++  
Only the C implementation will be created on build by default.  

```sh
git clone https://github.com/briansalehi/adjust-brightness.git
cd adjust-brightness
cmake -S . -B build -DCMAKE_BUILD_TYPE:STRING=release
cmake --build build --parallel
sudo cmake --build build --target install
```

To build C++ implementation, specify `cpp` as target.

*cpp build*
```sh
git clone https://github.com/briansalehi/adjust-brightness.git
cd adjust-brightness
cmake -S . -B build -DCMAKE_BUILD_TYPE:STRING=release
cmake --build build --target cpp --parallel
sudo cmake --build build --target install
```

To use Bash implementation, just copy the script in `prototype` directory
into your `PATH`:

```
cp prototype/adjust-brightness /usr/local/bin/
```

## Usage

Query current brightness by simply running the tool in your command line:

```sh
adjust-brightness
```

Or adjust brightness by giving a percent from 0 to 100 as program's parameter:

```sh
adjust-brightness 30
```

There are occasions when you have multiple monitors, in this case the program
asks you each time which monitor to use for query or adjustment.

## License

This work is licensed under [MIT License](LICENSE.md).
