#!/bin/sh
#
# Make an include tree to compile a generated header against: the
# netlink headers of a source tree, with finalize_sockaddr() in
# netlink_snl_route.h where the yanl branch of the base system puts it.
#
# usage: mkinclude.sh /usr/src out/include generated.h
#
# SPDX-License-Identifier: BSD-2-Clause

set -eu

src=$1
out=$2
header=$3

rm -rf "$out"
mkdir -p "$out"
cp -r "$src/sys/netlink" "$out/netlink"
cp "$header" "$out/netlink/"

route="$out/netlink/netlink_snl_route.h"
if ! grep -q finalize_sockaddr "$route"; then
	# Insert before the closing #endif of the include guard.
	awk -v f="$(dirname "$0")/finalize_sockaddr.h" '
		{ lines[NR] = $0 }
		END {
			last = NR
			while (last > 0 && lines[last] !~ /^#endif/)
				last--
			for (i = 1; i < last; i++)
				print lines[i]
			while ((getline l < f) > 0)
				print l
			for (i = last; i <= NR; i++)
				print lines[i]
		}' "$route" > "$route.new"
	mv "$route.new" "$route"
fi
