# Используем многоэтапную сборку
FROM fedora:latest AS builder

ENV HOME_PAGE=/app 
ENV VCPKG_ROOT=${HOME_PAGE}/vcpkg

# Устанавливаем зависимости
RUN dnf install -y dnf5 && \
    dnf5 install -y \
    @development-tools autoconf \
    clang clang-tools-extra \
    cmake libtool \
    perl cpanminus \
    ninja-build \
    mold lld \
    gtest gtest-devel \
    doxygen \
    glslang spirv-tools && \
    dnf clean all

# Копируем исходники
WORKDIR ${HOME_PAGE}
COPY . .

RUN git clone https://github.com/microsoft/vcpkg.git && \
    ${VCPKG_ROOT}/bootstrap-vcpkg.sh && \
    ${VCPKG_ROOT}/vcpkg integrate install


# Собираем проект
RUN mkdir -p build && cd build && \
    cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release && \
    cmake --build . --parallel $(nproc)

# Финальный образ
FROM fedora:latest

# Устанавливаем только необходимые для работы зависимости
RUN dnf install -y \
    libstdc++ \
    glibc \
    vulkan-loader && \
    dnf clean all

# Копируем собранные бинарники из builder-этапа
COPY --from=builder ${HOME_PAGE}/build/bin/ /usr/local/bin/
COPY --from=builder ${HOME_PAGE}/build/lib/ /usr/local/lib/

# Указываем точку входа
CMD ["/usr/local/bin/test"]