#!/usr/bin/env sh

# only run the build steps if there is no coverity scan ongoing
if [ "${COVERITY_SCAN_BRANCH}" != 1 ]; then
  set -evx
  mkdir build || true
  cd build
  cmake ../
  make
  CTEST_OUTPUT_ON_FAILURE=1 make test
fi 
