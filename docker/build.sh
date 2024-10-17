#!/bin/bash
# Login to the Docker registry
# docker login registry.ide3.de

# Build the Docker image
docker build -t registry.ide3.de/universumgames/mic-projekt .

# Push the Docker image
docker push registry.ide3.de/universumgames/mic-projekt