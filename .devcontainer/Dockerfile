# [Choice] noble (24.04), oracular (24.10), resolute (26.04)
ARG VARIANT="resolute"

FROM ubuntu:${VARIANT}

# Restate the variant to use it later on in the llvm and cmake installations
ARG VARIANT

ARG GCC_VER="16"

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive && \
    apt-get install -y --no-install-recommends \
	binutils \
    g++-${GCC_VER} gcc-${GCC_VER} cpp-${GCC_VER} \
	make \
	cmake \
	pkgconf \
    ca-certificates \
	git git-lfs \
	curl wget \
	gdb gdbserver \
	uuid-dev \
	doxygen doxygen-awesome-css graphviz \
	zsh \
 && rm -rf /var/lib/apt/lists/*

RUN update-alternatives --install /usr/bin/cpp cpp $(which cpp-${GCC_VER}) 100
RUN update-alternatives --install /usr/bin/gcc gcc $(which gcc-${GCC_VER}) 100
RUN update-alternatives --install /usr/bin/g++ g++ $(which g++-${GCC_VER}) 100

# Install editor(s)
RUN apt-get update -qq && export DEBIAN_FRONTEND=noninteractive && \
    apt-get install -y --no-install-recommends \
        vim neovim

RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

COPY ./.zshrc /root

ENV SHELL="/usr/bin/zsh"

WORKDIR /workspaces/cppdotnet

CMD ["/usr/bin/zsh"]
