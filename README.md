# Iris

Command line tool to adjust your screen's brightness (Linux only).

## Build

Download one of the packages in [Releases](https://github.com/briansalehi/iris/releases/latest):

*Debian*
```sh
sudo dpkg -i iris-*.deb
```

*Fedora*
```sh
sudo dnf install iris-*.rpm
```

*Build from source*
```sh
git clone https://github.com/briansalehi/adjust-brightness.git
cmake -S adjust-brightness -B build -D CMAKE_BUILD_TYPE=release
cmake --build build --parallel
sudo cmake --install build
```

## Usage

Query the current brightness of your screen:

```sh
adjust-brightness
```

Set brightness of your screen by passing percentage:

```sh
sudo adjust-brightness 33
```

**Note:** adjusting brightness requires root privileges.

## License

This work is licensed under [MIT License](LICENSE.md).
