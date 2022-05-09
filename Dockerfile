
FROM ubuntu:20.04

COPY . /code/
WORKDIR /code/

ENV DEBIAN_FRONTEND noninteractive

ENV COMPILE_GUI yes

# Remove the comment in the following line if you want to run unit tests in the container
#ENV COMPILE_TESTS yes

RUN bash /code/install_dep.sh

ENTRYPOINT bash /code/build_with_cmake.sh
