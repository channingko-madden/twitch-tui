# twitch-tui
Interact with Twitch in the terminal

## Requirements
- [Ninja](https://ninja-build.org/)
- [vcpkg](https://github.com/microsoft/vcpkg)

### Build

```sh
cmake --preset=default
cmake --build build
```

## Running

### config.toml

```toml
[twitch]
oauth = "..."
```
