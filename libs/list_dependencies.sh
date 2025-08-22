#!/bin/bash

for file in "$@"; do
  grep -E '^(import|#include)[[:space:]]*["<][^">]+[">]' "$file" | while read -r line; do
    kind=$(echo "$line" | grep -oE '^(import|#include)')
    path=$(echo "$line" | grep -oE '["<][^">]+[">]' | tr -d '<>"')
    type=$(echo "$line" | grep -qE '<' && echo "system" || echo "user")
    echo -e "${file}\t${kind}\t${type}\t${path}"
  done
done
