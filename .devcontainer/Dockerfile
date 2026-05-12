FROM ubuntu:26.04

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    g++-16 gcc-16 cpp-16 \
	make \
	cmake \
    ca-certificates \
	git git-lfs \
	curl \
	gdb gdbserver \
	uuid-dev \
	doxygen doxygen-awesome-css \
 && update-alternatives --install /usr/bin/cpp cpp /usr/bin/cpp-16 100 \
 && update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-16 100 \
 && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-16 100 \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /workspaces/cppdotnet

CMD ["bash"]
