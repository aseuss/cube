# only run the build steps if there is no coverity scan ongoing
if [ "${COVERITY_SCAN_BRANCH}" != 1 ]; then
  rm -rf build \
  && mkdir build \
  && cd build \
  && cmake ../ \
  && make
fi 
