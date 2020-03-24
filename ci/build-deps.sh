
DEPS_DIR=$( cd deps && pwd )

mkdir -p build/deps/install
DEPS_INSTALL_DIR=$( cd build/deps/install && pwd )

mkdir -p build/deps/googletest
pushd build/deps/googletest
cmake ${TARGET_PLATFORM:+-A ${TARGET_PLATFORM}} \
    "-DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL_DIR}" \
    -Dgtest_force_shared_crt=ON \
    -DBUILD_SHARED_LIBS=OFF \
    "${DEPS_DIR}/googletest"
cmake --build . --config RelWithDebInfo --target install -- -j3
popd

mkdir -p build/deps/abseil-cpp
pushd build/deps/abseil-cpp
cmake ${TARGET_PLATFORM:+-A ${TARGET_PLATFORM}} \
    "-DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL_DIR}" \
    -DBUILD_SHARED_LIBS=OFF \
    "${DEPS_DIR}/abseil-cpp"
cmake --build . --config RelWithDebInfo --target install -- -j3
popd