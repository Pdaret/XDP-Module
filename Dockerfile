FROM ubuntu:20.04

WORKDIR /build

RUN apt-get update; DEBIAN_FRONTEND=noninteractive apt-get -y install \
  bison build-essential cmake flex git libedit-dev libllvm7 llvm-7-dev \
  libclang-7-dev python zlib1g-dev libelf-dev libfl-dev python3-distutils \
  gcc-multilib vim git curl iproute2

RUN git clone https://github.com/iovisor/bcc.git
RUN mkdir bcc/build; cd bcc/build; cmake ..; make; make install

RUN apt-get install -y clang

RUN curl -s https://dl.google.com/go/go1.17.linux-amd64.tar.gz | tar -v -C /usr/local -xz
ENV GOPATH /go
ENV GOROOT /usr/local/go
ENV PATH $PATH:/usr/local/go/bin

WORKDIR /pdaret

COPY . .

RUN go build -o http-server http-server.go
CMD ["/pdaret/http-server"]


