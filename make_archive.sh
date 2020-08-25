#!/bin/sh
tar -cvjSf archives/bittino.tar.bz2 boards/* --transform 's,boards,AlienLogic,' >> /dev/null
echo "SHA-256:"
echo -n archives/bittino.tar.bz2 | sha256sum
echo "Size in bytes"
stat --printf="%s" archives/bittino.tar.bz2
echo "\n"
