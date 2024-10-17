#!/bin/bash
# Login to the Docker registry
# docker login registry.ide3.de

# Build the Docker image
docker buildx build --platform linux/amd64 -t registry.ide3.de/universumgames/mic-projekt/pio_build_esp32 .

# Push the Docker image
docker push registry.ide3.de/universumgames/mic-projekt/pio_build_esp32