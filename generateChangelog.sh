#!/bin/bash

echo "Generating CHANGELOG.md"
echo "" > CHANGELOG.md
echo "# Changelog" >> CHANGELOG.md
git log --pretty=format:"- (%h) %an, %ar : %s" >> CHANGELOG.md
