# Local Build Guide

Build the Toucan2 firmware locally using `west`.

## Prerequisites

- [Zephyr SDK](https://docs.zephyrproject.org/latest/develop/toolchains/index.html) (tested with 0.16.9)
- Python ≥3.8, `west`, `cmake`, `ninja`, `dtc`
- Environment variables set (adjust paths to your install):
  ```bash
  export ZEPHYR_TOOLCHAIN_VARIANT=zephyr
  export ZEPHYR_SDK_INSTALL_DIR=/opt/zephyr-sdk-0.16.9
  ```
- This repo initialized as a west workspace and dependencies fetched:
  ```bash
  cd toucan2-zmk/
  ## ONE-TIME: initialize this repo as the west manifest
  west init -l config
  ## Fetch ZMK, Zephyr, and all module sources (~5–10 min first time)
  west update
  ```

> **Note:** `zmk-helpers`, `zmk-adaptive-key`, and `zmk-tri-state` will be cloned into the workspace by `west update`. Do **not** commit them to git.

## Build Commands

Run all commands from the **workspace root** (`toucan2-zmk/`).  
Always specify `-d build/…` and use `--pristine` when starting fresh (avoids stale CMake cache).  
> ⚠️ Never run `west build` from inside a `build/` directory — that triggers the "source directory specified twice" error.

### Left half (nice!view + Studio + RGB LED)

> ⚠️ If you see a `ZephyrConfig.cmake` not found error, your shell may still have an old `ZEPHYR_BASE` environment variable exported. Run `unset ZEPHYR_BASE` first, or prefix every `west` command with it:
> ```bash
> unset ZEPHYR_BASE && west build ...
> ```

```bash
unset ZEPHYR_BASE && west build -s zmk/app -b seeeduino_xiao_ble \
  -d build/left -S studio-rpc-usb-uart \
  --pristine \
  -- -DSHIELD="toucan_left rgbled_adapter nice_view_gem" \
     -DZMK_CONFIG="$(pwd)/config" \
     -DZMK_EXTRA_MODULES="$(pwd)" \
     -DCONFIG_ZMK_STUDIO=y
```

### Right half (RGB LED)
```bash
west build -s zmk/app -b seeeduino_xiao_ble \
  -d build/right \
  --pristine \
  -- -DSHIELD="toucan_right rgbled_adapter" \
     -DZMK_CONFIG="$(pwd)/config" \
     -DZMK_EXTRA_MODULES="$(pwd)"
```

### Settings reset
```bash
west build -s zmk/app -b seeeduino_xiao_ble \
  -d build/reset \
  --pristine \
  -- -DSHIELD=settings_reset \
     -DZMK_CONFIG="$(pwd)/config" \
     -DZMK_EXTRA_MODULES="$(pwd)"
```

## Rebuilding without wiping the cache

`--pristine` forces a full clean rebuild. If you only changed the keymap and want a fast incremental build, drop `--pristine`:
```bash
west build -d build/left
```

> If west ever complains about "source directory specified twice", the build directory is stale. Delete it and use `--pristine`:
> ```bash
> rm -rf build/left && west build … --pristine
> ```

## What the flags mean

| Flag | Purpose |
|------|---------|
| `-s zmk/app` | Source directory inside the ZMK project fetched by `west` |
| `-b seeeduino_xiao_ble` | Target board (Seeed XIAO nRF52840) |
| `-d build/…` | Build output directory — **always set this** to avoid west auto-inference |
| `--pristine` | Wipes the build dir before CMake configuration |
| `-S studio-rpc-usb-uart` | Enable ZMK Studio RPC over USB-UART (left half only) |
| `-DSHIELD=…` | Composite shield list (split half + RGB adapter + display) |
| `-DZMK_CONFIG="$(pwd)/config"` | Absolute path to the keymap, Kconfig, and `.conf` files |
| `-DZMK_EXTRA_MODULES="$(pwd)"` | Absolute path so Zephyr sees this repo's shield definitions under `boards/shields/` |
| `-DCONFIG_ZMK_STUDIO=y` | Enables ZMK Studio keymap editing |

## Output

After successful builds, the UF2 files are:

- Left: `build/left/zephyr/zmk.uf2`
- Right: `build/right/zephyr/zmk.uf2`
- Reset: `build/reset/zephyr/zmk.uf2`

## Flashing

1. Connect the half you want to flash via USB.
2. Double-tap the reset button (or hold **BOOT** and press **RST**) to enter bootloader mode.
3. A mass-storage device named `XIAO-SENSE` appears.
4. Copy the matching `.uf2` onto that drive.
5. Repeat for the other half.

## Full clean

```bash
rm -rf build/
west update        # pull fresh module sources if desired
# Then re-run any of the pristine build commands above.
```

## Troubleshooting

- **`source directory specified twice`**: You either ran the command from inside `build/`, or your build directory has stale CMake cache. Run from the workspace root, always pass `-d`, and use `--pristine`.
- **`west update` fails on module fetch**: These repos default to `master`; our `west.yml` pins them to `main`. If you see `couldn't find remote ref master`, ensure you're on the latest commit that includes the `revision: main` fix.
- **`zmk.keymap` not found**: Ensure `-DZMK_CONFIG` is an absolute path. Use `"$(pwd)/config"`.
- **Shield not found during build**: Ensure `-DZMK_EXTRA_MODULES="$(pwd)"` is set so Zephyr sees `boards/shields/toucan/`, `nice_view_gem/`, etc.
