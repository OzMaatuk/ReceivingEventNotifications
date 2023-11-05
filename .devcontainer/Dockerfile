FROM mcr.microsoft.com/devcontainers/cpp:1-debian-11

ARG REINSTALL_CMAKE_VERSION_FROM_SOURCE="3.22.2"

# Optionally install the cmake for vcpkg
COPY ./*.sh /tmp/

RUN if [ "${REINSTALL_CMAKE_VERSION_FROM_SOURCE}" != "none" ]; then \
        chmod +x /tmp/reinstall-cmake.sh && /tmp/reinstall-cmake.sh ${REINSTALL_CMAKE_VERSION_FROM_SOURCE}; \
    fi \
    && rm -f /tmp/reinstall-cmake.sh

RUN git config core.filemode false

RUN git config --global core.autocrlf true

# Install booststacktrace
RUN chmod +x /tmp/reinstall-booststacktrace.sh && /tmp/reinstall-booststacktrace.sh

# Install glog
RUN chmod +x /tmp/reinstall-glog.sh && /tmp/reinstall-glog.sh

# Install gtest
RUN chmod +x /tmp/reinstall-gtest.sh && /tmp/reinstall-gtest.sh

# Install inotify
RUN chmod +x /tmp/reinstall-inotify.sh && /tmp/reinstall-inotify.sh

# Install jsoncpp
RUN chmod +x /tmp/reinstall-jsoncpp.sh && /tmp/reinstall-jsoncpp.sh

# Install libc
# RUN chmod +x /tmp/reinstall-libc.sh && /tmp/reinstall-libc.sh

# [Optional] Uncomment this section to install additional vcpkg ports.
# RUN su vscode -c "${VCPKG_ROOT}/vcpkg install <your-port-name-here>"

# [Optional] Uncomment this section to install additional packages.
# RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
#     && apt-get -y install --no-install-recommends <your-package-list-here>