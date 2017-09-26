#!/usr/bin/env /bin/bash

source ../test/common.sh

rm -f program libnumber.so

[[ -r Makefile ]] || die "No Makefile present"

msg "Running make"
make || die "Running 'make' failed"

[[ -x program ]] || die "program was not created (or is not executable)"
[[ -x libnumber.so ]] || die "libnumber.so was not created (or is not executable)"

make clean || die "Running 'make clean' failed"

# TODO: we don't really know what the aux files might have been
# checking generally for everything before  + targets is a bit more complicated
[[ -x program ]] || die "program was removed by clean"
[[ -x libnumber.so ]] || die "libnumber.so was removed by clean"

touch libnumber.so program.c
sleep 1
make || die "Re-running make failed"

[[ program -nt program.c ]] || die "program was not rebuilt!"
# note: this might actually fail
[[ libnumber.so -nt program.c ]] && warn "libnumber.so was rebuilt when it should not"

make distclean || die "Running 'make distclean' failed"

[[ -e program ]] && die "program was not removed by distclean"
[[ -e libnumber.so ]] && die "libnumber.so was not removed by distclean"

make distclean || die "Running 'make distclean' twice in a row should not fail!"

msg "Passed"

# vim: set sw=4 sts=4 ts=4 noet :
