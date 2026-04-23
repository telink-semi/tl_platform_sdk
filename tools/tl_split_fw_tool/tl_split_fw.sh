#!/bin/bash
input_file="$1.elf"; base_name="${input_file%.*}"; output_file="${base_name}_NVM"; riscv32-elf-objcopy -O binary --only-section=.nvm_code --only-section=.nvm_rodata --only-section=.nvm_rwdata_nocopy --only-section=.nvm_rwdata_copy "$input_file" "$output_file.bin"; [ -s "$output_file.bin" ] || rm -f "$output_file.bin"
