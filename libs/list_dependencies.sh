#!/bin/bash

for file in "$@"; do
  grep -E '^(import|#include|export import)[[:space:]]*(["<][^">]+[">]|[a-zA-Z:_]+)' "$file" | while read -r line; do
    kind=$(echo "$line" | grep -oE '^(import|#include|export import)')
    path=$(echo "$line" | grep -oP '(?<=[[:space:]])(["<][^">]+[">]|[a-zA-Z:_]+)(?=;)' | tr -d '<>"')
    type=$(echo "$line" | grep -qE '<' && echo "system" || echo "user")
    echo -e "${file}\t${kind}\t${type}\t${path}"
  done
done
