/*
**  igmpproxy - IGMP proxy based multicast router 
**  Copyright (C) 2005 Johnny Egeland <johnny@rlo.org>
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation; either version 2 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**
**----------------------------------------------------------------------------
**
**  This software is derived work from the following software. The original
**  source code has been modified from it's original state by the author
**  of igmpproxy.
**
**  smcroute 0.92 - Copyright (C) 2001 Carsten Schill <carsten@cschill.de>
**  - Licensed under the GNU General Public License, version 2
**  
**  mrouted 3.9-beta3 - COPYRIGHT 1989 by The Board of Trustees of 
**  Leland Stanford Junior University.
**  - Original license can be found in the "doc/mrouted-LINCESE" file.
**
*/


#include "defs.h"
#include <net/if.h>

int curttl = 0;

void k_set_rcvbuf(int bufsize, int minsize)
{
    int delta = bufsize / 2;
    int iter = 0;

    /*
     * Set the socket buffer.  If we can't set it as large as we
     * want, search around to try to find the highest acceptable
     * value.  The highest acceptable value being smaller than
     * minsize is a fatal error.
     */
    if (setsockopt(MRouterFD, SOL_SOCKET, SO_RCVBUF,
                   (char *)&bufsize, sizeof(bufsize)) < 0) 
    {
        bufsize -= delta;
        while (1) 
        {
            iter++;
            if (delta > 1)
                delta /= 2;

            if (setsockopt(MRouterFD, SOL_SOCKET, SO_RCVBUF, (char *)&bufsize, sizeof(bufsize)) < 0) 
            {
                bufsize -= delta;
            } 
            else 
            {
                if (delta < 1024)
                    break;
                bufsize += delta;
            }
        }
        if (bufsize < minsize) 
        {
            atlog(LOG_ERR, 0, "OS-allowed buffer size %u < app min %u",
                bufsize, minsize);
            /*NOTREACHED*/
        }
    }
    IF_DEBUG atlog(LOG_DEBUG, 0, "Got %d byte buffer size in %d iterations", bufsize, iter);
}


void k_set_ttl(int t) 
{
    if( setsockopt( MRouterFD, IPPROTO_IPV6, IPV6_MULTICAST_HOPS, &t, sizeof( t ) ) != 0 )
        atlog(LOG_ERR, errno, "set IPV6_MULTICAST_HOPS failed" );
}


void k_set_loop(int Va) 
{
    int a = 0;
    if (setsockopt(MRouterFD, IPPROTO_IPV6, IPV6_MULTICAST_LOOP, &a, sizeof(int)) == -1 )   
    {
        atlog(LOG_ERR, errno, "ICMPV6 setsockopt IPV6_MULTICAST_LOOP = 0 failed, MRouterFD = %d error = %d\n",MRouterFD, errno);
    }
}

uint32 k_get_ifindex(char *ifname)
{
/*to be fill*/
    return if_nametoindex(ifname);
}

uint32 k_set_if(uint32 new_mcast_ifindex) 
{
    uint32 old_mcast_ifindex = 0;
    int arg_len = sizeof(old_mcast_ifindex);

    if (getsockopt(MRouterFD, IPPROTO_IPV6, IPV6_MULTICAST_IF, (char *)&old_mcast_ifindex, (socklen_t *)&arg_len) < 0)
        atlog(LOG_ERR, errno, "getsockopt IP_MULTICAST_IF");

    if (setsockopt(MRouterFD, IPPROTO_IPV6, IPV6_MULTICAST_IF, (char *)&new_mcast_ifindex, sizeof(new_mcast_ifindex)) < 0)
        atlog(LOG_ERR, errno, "setsockopt IP_MULTICAST_IF");

    return old_mcast_ifindex;
}

void joinReportGroup()
{
    unsigned Ix;
    struct IfDesc *Dp;

    // Join the all routers group on downstream vifs...
    for ( Ix = 0; (Dp = getIfByIx( Ix )); Ix++ ) 
    {
        // If this is a downstream vif, we should join the All routers group...
        if( Dp->state == IF_STATE_DOWNSTREAM ) 
        {
            joinMcGroup( MRouterFD, Dp, &mld_report_group );
        }
    }
}

/*
void k_join(uint32 grp, uint32 ifa) 
{
    struct ip_mreq mreq;

    mreq.imr_multiaddr.s_addr = grp;
    mreq.imr_interface.s_addr = ifa;

    if (setsockopt(MRouterFD, IPPROTO_IP, IP_ADD_MEMBERSHIP,
                   (char *)&mreq, sizeof(mreq)) < 0)
        atlog(LOG_WARNING, errno, "can't join group %s on interface %s",
            inetFmt(grp, s1), inetFmt(ifa, s2));
}


void k_leave(uint32 grp, uint32 ifa) {
    struct ip_mreq mreq;

    mreq.imr_multiaddr.s_addr = grp;
    mreq.imr_interface.s_addr = ifa;

    if (setsockopt(MRouterFD, IPPROTO_IP, IP_DROP_MEMBERSHIP,
                   (char *)&mreq, sizeof(mreq)) < 0)
        atlog(LOG_WARNING, errno, "can't leave group %s on interface %s",
            inetFmt(grp, s1), inetFmt(ifa, s2));
}
*/