#!/bin/bash

gitUrl=$(git remote get-url origin)

echo "Generating CHANGELOG.md"
echo "" > CHANGELOG.md
echo "# Changelog" >> CHANGELOG.md

git log --pretty=format:"- ([%h]($gitUrl/-/commit/%H)) %an on [%as](## \"%aD\") : %s" >> CHANGELOG.md
