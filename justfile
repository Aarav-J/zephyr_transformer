# ------------------
#  Configurables
# ------------------

SIM_BOARD := "qemu_cortex_m3"
ESP_BOARD := "esp32s3_devkitc/esp32s3/procpu"
ESP_PORT := "/dev/cu.SLAB_USBtoUART"
CMAKE_CACHE_ARGS := "-- -DCMAKE_EXPORT_COMPILE_COMMANDS=ON"
WEST_WORKSPACE := "/Users/aaravjain/Desktop/CODE/zephyr-workspace/zephyr"
APP_DIR := justfile_directory()
BUILD_DIR := justfile_directory() + "/build"
export PATH := justfile_directory() + "/.venv/bin:" + env("PATH")

set shell := ["bash", "-eu", "-o", "pipefail", "-c"]
set working-directory := "/Users/aaravjain/Desktop/CODE/zephyr-workspace/zephyr"

# ------------------
#  Helpers
# ------------------

_verify_workspace:
    test -f .west/config || { echo "ERROR: West workspace config missing in {{ WEST_WORKSPACE }}/.west/config."; exit 1; }
    test -x "{{ justfile_directory() }}/.venv/bin/west" || { echo "ERROR: Create zephyr_transformer/.venv with Python 3.12+ and install Zephyr's requirements.txt + esptool + pyserial."; exit 1; }

# ------------------
#  Sim (QEMU)
# ------------------

build-sim: _verify_workspace clean
    west build \
      -p always \
      -b {{ SIM_BOARD }} \
      -d "{{ BUILD_DIR }}" \
      "{{ APP_DIR }}" \
      {{ CMAKE_CACHE_ARGS }}

run-sim: build-sim
    west build -t run -d "{{ BUILD_DIR }}"

# ------------------
#  ESP32-S3
# ------------------

build-esp32: _verify_workspace clean
    west build \
      -p always \
      -b "{{ ESP_BOARD }}" \
      -d "{{ BUILD_DIR }}" \
      "{{ APP_DIR }}" \
      {{ CMAKE_CACHE_ARGS }}

flash-esp32:
    west flash --build-dir "{{ BUILD_DIR }}" --esp-device "{{ ESP_PORT }}"

monitor-esp32:
    python -m serial.tools.miniterm "{{ ESP_PORT }}" 115200

run-esp32: build-esp32 flash-esp32 monitor-esp32

# ------------------
#  Defaults
# ------------------

clean:
    rm -rf "{{ BUILD_DIR }}"
