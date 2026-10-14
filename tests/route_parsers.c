#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netlink/netlink.h>
#include <netlink/netlink_route.h>
#include <netlink/netlink_snl.h>
#include <netlink/netlink_snl_route.h>
#include <netlink/netlink_snl_route_parsers.h>

static const struct snl_hdr_parser *all_parsers[] = {
	&snl_rtm_route_parser, &snl_rtm_link_parser, &snl_rtm_link_parser_simple,
	&snl_rtm_neigh_parser, &snl_rtm_addr_parser, &snl_nhmsg_parser,
	&_mpath_nh_parser, &_vf_parser, &_vf_status_parser, &_vf_driver_parser,
	&_vf_driver_field_parser, &_ifgroups_parser,
};

int
main(void)
{
	struct snl_parsed_link link = {};
	struct snl_parsed_route route = {};
	struct snl_parsed_neigh neigh = {};
	struct snl_parsed_addr addr = {};
	struct snl_parsed_nhop nh = {};
	struct snl_parsed_link_simple ls = {};
	struct rta_mpath_nh mp = {};
	struct snl_parsed_vf vf = {};

	SNL_VERIFY_PARSERS(all_parsers);
	return (link.ifi_index + link.ifla_mtu + (link.ifla_ifname != NULL) +
	    (link.iflaf_caps.nla_bitset_size) + link.iflaf_groups.count +
	    link.iflaf_vf_status.vfs.count + link.ifla_num_vf +
	    (link.iflaf_orig_hwaddr != NULL) + (link.ifla_address != NULL) +
	    (link.ifla_ifalias != NULL) + link.ifi_flags + link.ifi_type +
	    (route.rta_dst != NULL) + (route.rta_gw != NULL) + route.rta_oif +
	    route.rta_table + route.rta_multipath.count + route.rtm_family +
	    route.rtm_type + route.rtm_protocol + route.rtm_dst_len +
	    route.rtax_mtu + route.rta_metric + route.rta_nh_id + route.rta_knh_id +
	    route.rta_rtflags + route.rta_expire + (route.rta_pref_src != NULL) +
	    (neigh.nda_dst != NULL) + (neigh.nda_lladdr != NULL) + neigh.nda_probes +
	    neigh.ndaf_next_ts + neigh.ndm_flags + neigh.ndm_state + neigh.nda_ifindex +
	    (addr.ifa_address != NULL) + addr.ifa_family + addr.ifa_index +
	    addr.ifa_prefixlen + (addr.ifa_local != NULL) + addr.ifaf_vhid +
	    (addr.ifa_cacheinfo != NULL) + nh.nhaf_aif + (nh.nha_gw != NULL) +
	    nh.nha_oif + nh.nh_family + nh.nha_id + ls.ifi_index + ls.ifla_mtu +
	    (mp.gw != NULL) + mp.ifindex + mp.rta_expire + mp.rta_metric +
	    mp.rtax_mtu + mp.rtnh_weight + mp.rtnh_flags + mp.rta_rtflags +
	    (int)vf.attrs + vf.index + vf.drivers.count);
}
