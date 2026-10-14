# yanl: generate snl(3) parsers from the FreeBSD netlink YANG modules.
#
# YANG is the directory of the protocol modules of one release (the
# spmzt/yang repository, or sys/netlink/specs in the base system); the
# binding modules are in its snl/ subdirectory, or beside them.

LUA?=		/usr/libexec/flua
YANG?=		../yang/16-CURRENT
BINDINGS?=	${YANG}/snl
OUT?=		out
CC?=		cc

YANL=		${LUA} ${.CURDIR}/yanl.lua -p ${YANG} -p ${BINDINGS}

ROUTE_BINDINGS=	freebsd-rtnetlink-route-snl	\
		freebsd-rtnetlink-link-snl	\
		freebsd-rtnetlink-neigh-snl	\
		freebsd-rtnetlink-addr-snl	\
		freebsd-rtnetlink-nexthop-snl

all: ${OUT}/netlink_snl_route_parsers.h

${OUT}/netlink_snl_route_parsers.h: yanl.lua lib/*.lua
	mkdir -p ${OUT}
	${YANL} -o ${.TARGET} ${ROUTE_BINDINGS}

# Compile the generated header against the kernel's headers of the
# tree in SRC, with the snl_route.h of the yanl branch (finalize_sockaddr
# moves there), and check the parsers' tables are sorted.
SRC?=		/usr/src

check: all
	sh tests/mkinclude.sh ${SRC} ${OUT}/include \
	    ${OUT}/netlink_snl_route_parsers.h
	${CC} -Wall -Wextra -Werror -std=gnu17 -I${OUT}/include \
	    -o ${OUT}/route_parsers tests/route_parsers.c
	${OUT}/route_parsers
	@echo "check: ok"

clean:
	rm -rf ${OUT}

.PHONY: all check clean
