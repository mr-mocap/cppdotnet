#!/usr/bin/env bash
# normalize_deps.sh

input="$1"
output="$2"

sed -E 's/([^[:space:]]*):([^[:space:]]*)\.c\+\+m/\1\\:\2.ixx/g' "$input" > "$output"
