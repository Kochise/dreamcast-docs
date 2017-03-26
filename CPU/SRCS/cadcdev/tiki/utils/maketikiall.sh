#!/bin/sh

find . -iname "*.h" | cut -b 3- | sed -e 's@^@#include <Tiki/@' | sed -e 's@$@>@'
