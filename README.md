# Adjust Brightness

Command line tool to adjust your screen's brightness.

This tool only works on Linux systems.

## Setup

```sh
git clone https://github.com/briansalehi/adjust-brightness.git
cd adjust-brightness
cmake -S . -B build -DCMAKE_BUILD_TYPE:STRING=release
cmake --build build --parallel
sudo cmake --build build --target install
```

## Usage

You can query current brightness by simply running the tool
in your command line:

```sh
adjust-brightness
```

Or adjust brightness by giving a percent from 0 to 100 as
program's parameter:

```sh
adjust-brightness 30
```

## License

This work is licensed under [MIT License](LICENSE.md).
