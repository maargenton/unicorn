
```sh
docker run -it --rm -v $(pwd):/workdir \
    -e CROSS_TRIPLE=x86_64-apple-darwin \
    multiarch/crossbuild \
    ./build.sh

docker run -it --rm -v $(pwd):/workdir \
    -e CROSS_TRIPLE=x86_64-w64-mingw32 \
    multiarch/crossbuild \
    ./build.sh

docker run -it --rm -v $(pwd):/workdir \
    -e CROSS_TRIPLE=x86_64-linux-gnu \
    multiarch/crossbuild \
    ./build.sh

docker run -it --rm -v $(pwd):/workdir \
    -e CROSS_TRIPLE=arm-linux-gnueabi \
    multiarch/crossbuild \
    ./build.sh

docker run -it --rm -v $(pwd):/workdir \
    -e CROSS_TRIPLE=aarch64-linux-gnu \
    multiarch/crossbuild \
    ./build.sh

```
