# Use an official image as a base
FROM ubuntu:latest

# Set the working directory in the container
WORKDIR /app

# Install git, ssh, and other necessary packages
RUN apt-get update && apt-get install -y git ssh cmake

# Add the SSH private key to the container
COPY id_rsa /root/.ssh/id_rsa
RUN chmod 600 /root/.ssh/id_rsa

# Add GitHub to the list of known hosts
RUN ssh-keyscan github.com >> /root/.ssh/known_hosts

# Clone the repository using SSH
RUN git clone git@github.com:EpitechPromo2026/B-CPP-500-PAR-5-1-rtype-alberick.mahoussi.git

# Change the directory to the cloned repository
WORKDIR /app/B-CPP-500-PAR-5-1-rtype-alberick.mahoussi

# Initialize and update git submodules
RUN git submodule init && git submodule update

# Create build directory and move into it
RUN mkdir build && cd build

# Run CMake to build the project
RUN cmake .. -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release

# Build the project
RUN cmake --build .

# Expose the required port for the server
EXPOSE 4242

# Run the server and client
CMD ["sh", "-c", "./r-type_server 4242 && ./r-type_client"]


