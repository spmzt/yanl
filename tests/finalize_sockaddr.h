
/* Fill in the scope of a link-local address from the interface index. */
static inline void
finalize_sockaddr(struct sockaddr *sa, uint32_t ifindex)
{
	if (sa != NULL && sa->sa_family == AF_INET6) {
		struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)(void *)sa;

		if (IN6_IS_ADDR_LINKLOCAL(&sin6->sin6_addr))
			sin6->sin6_scope_id = ifindex;
	}
}
