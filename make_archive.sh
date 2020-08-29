#!/bin/sh
tar -cvjSf archives/bittino.tar.bz2 boards/* --transform 's,boards,AlienLogic,' >> /dev/null
CHECKSUM=$(sha256sum archives/bittino.tar.bz2 | cut -d " " -f 1)
SIZE=$(stat --printf="%s" archives/bittino.tar.bz2)

node apply_archive_json.js $CHECKSUM $SIZE
echo "SHA-256: $CHECKSUM"
echo "Size in bytes: $SIZE"
echo "\n"
