#!/bin/bash

hash=$(find ./src -type f -print0 | sort -z | xargs -0 sha1sum | sha1sum)

echo '#pragma once' > ./lib/basic/versionHash.h
echo '#define VERSION_HASH "$hash"' >> ./lib/basic/versionHash.h