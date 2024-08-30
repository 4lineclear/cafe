cmake:
    mkdir -p build && cd build && cmake .. && make
make:
    cd build && make
test:
    cd build && make test
clean:
    rm -rf ./build/
