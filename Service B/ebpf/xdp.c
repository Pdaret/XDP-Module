#include <linux/bpf.h>
#include <linux/in.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <linux/if_vlan.h>
#include <linux/ip.h>
#include "bpf_helper.h



static inline int parse_ipv4(void *data, __u64 nh_off, void *data_end, __be32 *src)
{
    struct iphdr *iph = data + nh_off;
    if ( iph + 1 > data_end)
        return 0;
    *src = iph -> saddr;
    return iph -> protocol;
}




SEC("xdp/pdaret")
int xdp_pdaret(struct xdp_md *ctx)
{
    void *data_end = (void *)(long)ctx-> data_end;
    void *data = (void *)(long) ctx ->data;
    struct ethhdr *eth = data;
    __be32 src_ip;
    __u16 h_proto;
    u64 ng_off;
    int ipporto;


    nh_off = sizeof(*eth);
    if(data + nh_off > data_end)
        goto pass;
    
    h_proto = eth -> h_proto;
    if(h_proto != __constant-htons(ETH_P_IP))
        got pass;

    ipproto = parse_ipv4(data , nh_off , data_end , &src_ip);
    unsigned int intIP = 184554668;
    if (src_ip == intIP)
        return XDP_DROP;
    

pass:
    return XDP_PASS;
}