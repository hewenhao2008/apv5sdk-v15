#ifndef __CAPWAP_WTPDriverinteraction_HEADER__
#define __CAPWAP_WTPDriverinteraction_HEADER__
#include "CWWTP.h"

#if 0
#ifndef NO_USE_MADWIFI
#include <ath/if_athioctl.h>
#include <net80211/ieee80211_crypto.h>
#include <net80211/ieee80211.h>
#include <net80211/_ieee80211.h>
#include <net80211/ieee80211_ioctl.h>
#include <net80211/ieee80211_node.h>
#endif
#endif

#ifndef IFNAMSIZ
#define IFNAMSIZ 16/*I add*/
#endif

#define SIOCDEVPRIVATE	0x89F0	/* to 89FF */

typedef unsigned char		u_int8_t;
typedef unsigned short		u_int16_t;
typedef unsigned int 	u_int32_t;
typedef signed char 	int8_t;
typedef unsigned long long u_int64_c;

/* pei add for rogue AP test .  1118 */
enum opstate {
	NEW=1,
	DELETE,
	MODIFIED,
	REMAIN,
};
enum interfaceType {
	ATH=0,
	ETH,
	WIFI,
};

typedef struct {
	unsigned char radio_id;
	unsigned char id;
	unsigned char updown_time;
} interface_updown_time;

typedef struct {  //pei add 0415
	unsigned char id;
	unsigned char status;  //0-not exist,1-up,2-down,3-error
} interface_status;

typedef struct {  //pei add 0422
	unsigned char eth_count;
	interface_status *eth_status;
	unsigned char wifi_count;
	interface_status *wifi_status;
} ifState;

typedef struct {
	unsigned char value;
	unsigned char count;
	unsigned char is_flood_attack;
	unsigned char flood_detect_type;  // 0
	unsigned char flood_sta_mac[6];
	unsigned char flood_vap_mac[6];
	unsigned char flood_frame_type;
	unsigned char flood_channel;
	unsigned char flood_rssi;
	unsigned char is_spoof_attack;
	unsigned char spoof_detect_type;  // 1
	unsigned char spoof_sta_mac[6];
	unsigned char spoof_vap_mac[6];
	unsigned char spoof_frame_type;
	unsigned char spoof_channel;
	unsigned char spoof_rssi;
	unsigned char is_weakiv_attack;
	unsigned char weakiv_detect_type;  // 2
	unsigned char weakiv_sta_mac[6];
	unsigned char weakiv_vap_mac[6];
	unsigned char weakiv_payload;
	unsigned char weakiv_channel;
	unsigned char weakiv_rssi;
} attackDetectInfo;

typedef struct {
	unsigned char value;
	/* 4 bytes reserved */
	unsigned short count;
	unsigned char radio_id;
	unsigned char wlan_id;
	unsigned char state;  /* 1-warn, 0-no */
	unsigned char sta_mac[6];
} attackAddrRedirectionInfo;

typedef struct {
	unsigned char optype;
	unsigned short int len;
	unsigned char sta_mac[6];
	unsigned int frames_recv;
	unsigned int frames_send;
	unsigned long long int bytes_recv;
	unsigned long long int bytes_send;
}staThroughputsendtoAc;

typedef struct {
	unsigned char value;
	/* 4 bytes reserved */
	unsigned short count;
	unsigned char radio_id;
	unsigned char wlan_id;
	unsigned char state;  /* 1-warn, 0-no */
	unsigned char sta_mac[6];
} challengeReplayInfo;

typedef struct {
	unsigned char value;
	unsigned char radio_id;
	unsigned char wlan_id;
	unsigned char state;  /* 1-warn, 0-no */
	/* 4 bytes reserved */
	unsigned short sta_count;
	unsigned char *sta_mac;
} terminalDisturbInfo;

typedef struct {
	unsigned int wpi_replay_error;
	unsigned int wpi_decryp_error;
	unsigned int wpi_mic_error;
} wpi_errors;

typedef struct {
	unsigned int disassoc_unnormal;
	unsigned int rx_assoc_norate;
	unsigned int rx_assoc_capmismatch;
	unsigned int assoc_invalid;
	unsigned int reassoc_deny;
} disassoc_errors;

typedef struct {
	int cpu_use_ratio;
	unsigned int tx_mgmt;
	unsigned int rx_mgmt;
	unsigned int tx_packets;
	unsigned int tx_errors;
	unsigned int tx_retry;
	unsigned int tx_unicast; /* pei add for eth at 090624 */
	unsigned int tx_broadcast;
	unsigned int tx_multicast;
	unsigned int tx_drop;
	unsigned int rx_unicast;
	unsigned int rx_broadcast;
	unsigned int rx_multicast;
	unsigned int rx_drop; /* end. pei add for eth at 090624 */
	unsigned int wpi_replay_error;
	unsigned int wpi_decryp_error;
	unsigned int wpi_mic_error;
	unsigned int disassoc_unnormal;
	unsigned int rx_assoc_norate;
	unsigned int rx_assoc_capmismatch;
	unsigned int assoc_invalid;
	unsigned int reassoc_deny;
	unsigned char get_Ip_mode;
	unsigned short mem_total;
	unsigned char mem_use_ratio;
	unsigned short flash_total;
	int flash_free;
	unsigned char snr;
	char temperature;  //pei add 0415
	unsigned char eth_count;
	interface_updown_time *eth_updown_time;
	unsigned char ath_count;
	interface_updown_time *ath_updown_time;
	unsigned char wifi_count;  //pei add 0415
	interface_status *wifi_status;  //pei add 0415
} extra_info;

/* caisicong my  led need */
typedef struct wrcpu_op_args_s {
	unsigned long  op_addr;
	unsigned long  op_value; // ignore on read in arg, fill read value on write return value
	unsigned short op_byteorder; // destination byte order. default is bigendiana.
	unsigned short op_len;
	unsigned short op_ret; // 0 for success, other value indicate different failure.
	unsigned int num;//which gpio
	unsigned int status;/*0 off 1 on*/
	unsigned char basemac[6];
	unsigned char boardID[20];/*wtp sn*/
	unsigned int factory_reset_get;
#ifdef AQ2010
	unsigned char OEM_INFO[64];  /* rbk add 090107 */
#endif
} wrcpu_op_args;

#define WRCPU_IOC_MAGIC 10
#define WRCPU_IOC_G_  _IOWR(WRCPU_IOC_MAGIC,1,wrcpu_op_args) // read values
#define WRCPU_IOC_X_ _IOWR(WRCPU_IOC_MAGIC,2,wrcpu_op_args) // write and readout wrote value
#define WRCPU_IOC_S_ _IOWR(WRCPU_IOC_MAGIC,3,wrcpu_op_args)//set the select
#define WRCPU_IOC_D_ _IOWR(WRCPU_IOC_MAGIC,4,wrcpu_op_args)//down the blind timer
#define WRCPU_IOC_U_ _IOWR(WRCPU_IOC_MAGIC,5,wrcpu_op_args)/*up the blinding*/ 
#define WRCPU_IOC_B_ _IOWR(WRCPU_IOC_MAGIC,6,wrcpu_op_args)//blue led on 
#define WRCPU_IOC_I_ _IOWR(WRCPU_IOC_MAGIC,7,wrcpu_op_args)/*get the sysinf*/
#define WRCPU_FLASH_W_ _IOWR(WRCPU_IOC_MAGIC,8,wrcpu_op_args)/*write flash*/
#define WRCPU_WATCHDOG _IOWR(WRCPU_IOC_MAGIC,9,wrcpu_op_args)/*write watchdog*/
#define FACTORY_RESET _IOWR(WRCPU_IOC_MAGIC,10,wrcpu_op_args)/*open factory reset*/
#define WRCPU_IOC_MAXNR 15

/* peiwenhui add 0703 --netlink */
#ifndef MSG_DONTWAIT
#define MSG_DONTWAIT 0
#endif

#ifndef IFLA_WIRELESS
#define IFLA_WIRELESS 11
#endif
#define NETLINK_ROUTE 0
#define RTMGRP_LINK 1
#define RTM_BASE 0x10
#define RTM_NEWLINK (RTM_BASE + 0)
#define NLMSG_ALIGNTO 4
#define NLMSG_ALIGN(len) (((len) + NLMSG_ALIGNTO - 1) & ~(NLMSG_ALIGNTO - 1))
#define NLMSG_LENGTH(len) ((len) + NLMSG_ALIGN(sizeof(struct nlmsghdr)))
#define NLMSG_DATA(nlh) ((void*) (((char*) nlh) + NLMSG_LENGTH(0)))

#define RTA_ALIGNTO 4
#define RTA_ALIGN(len) (((len) + RTA_ALIGNTO - 1) & ~(RTA_ALIGNTO - 1))
#define RTA_OK(rta,len) \
((len) > 0 && (rta)->rta_len >= sizeof(struct rtattr) && \
(rta)->rta_len <= (len))
#define RTA_NEXT(rta,attrlen) \
((attrlen) -= RTA_ALIGN((rta)->rta_len), \
(struct rtattr *) (((char *)(rta)) + RTA_ALIGN((rta)->rta_len)))

/* for wapi attack addr redirection trap -- pei add 20100911 */
/*Driver ���͵Ĺ��ڹ���STA����Ϣ*/								
struct asso_mt_t
{
	//struct nlmsghdr hdr;		/**/
	u16		type;		/*��Ϣ����*/
	u16		data_len;		/*��Ϣ����*/
#if 1  /*czm modified,temp*/
	u8		chan_old;
	u8		chan_curr;
#endif 
	u8 		ap_mac[6];
	u8 		pad1[2];
	u8		mac[6];		/*STA ��MAC��ַ*/
	u8 		pad[2];
	u8		gsn[16];		/*�鲥�������*/
	u8		wie[256];		/*wapi��ϢԪ��*/
};
typedef struct asso_mt_t asso_mt;
/* end */
#ifndef CONFIG_NO_SOCKLEN_T_TYPEDEF
#ifndef __socklen_t_defined
typedef int socklen_t;
#endif
#endif

/*
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
*/

struct ifinfomsg
{
	unsigned char ifi_family;
	unsigned char __ifi_pad;
	unsigned short ifi_type;
	int ifi_index;
	unsigned ifi_flags;
	unsigned ifi_change;
};
struct nlmsghdr
{
	u32 nlmsg_len;
	u16 nlmsg_type;
	u16 nlmsg_flags;
	u32 nlmsg_seq;
	u32 nlmsg_pid;
};
struct rtattr
{
	unsigned short rta_len;
	unsigned short rta_type;
};
struct sockaddr_nl
{
	sa_family_t nl_family;
	unsigned short nl_pad;
	u32 nl_pid;
	u32 nl_groups;
};

/* Begin: gengzj added for wifipos 2013-11-25 */
#define NETLINK_GENERIC 16
#define NETLINK_DETECTOR_WTPD (NETLINK_GENERIC + 4) /* detector��wtpd֮���netlinkͨ��Э������ */

struct atnlmsghdr
{
    unsigned char domain;
    unsigned char version;
    unsigned short attr_count;
    unsigned int reserved;
    unsigned int original_src_pid;
    unsigned int original_dst_pid;
};
/* End: gengzj added end */

/* peiwenhui add 090205 --- for get wlan throughput info */
#define _PATH_PROCNET_DEV               "/proc/net/dev"
#define is_space(c) ((((c) == ' ') || (((unsigned int)((c) - 9)) <= (13 - 9))))
#define NUM_OF_ATH_ALL_WIFI	16
#define NUM_OF_WIFI			2
#define NUM_OF_ETH			2

/* peiwenhui add 090625 --- for get attack detect info */
#define IEEE80211_WIDS_FLOOD_DETECT 0x01
#define IEEE80211_WIDS_SPOOF_DETECT 0x02
#define IEEE80211_WIDS_WEAKIV_DETECT 0x03

#define IEEE80211_WIDS_FPROBE_REQUEST 0x01
#define IEEE80211_WIDS_FAUTH_REQUEST 0x02
#define IEEE80211_WIDS_FASSOC_REQUEST 0x03
#define IEEE80211_WIDS_FREASSOC_REQUEST 0x04
#define IEEE80211_WIDS_FDEAUTH_REQUEST 0x05
#define IEEE80211_WIDS_FDISASSO_REQUEST 0x06
#define IEEE80211_WIDS_FNULL_DATA 0x07
#define IEEE80211_WIDS_FACTION 0x08

#define IEEE80211_WIDS_SPOOF_DEAUTH 0x01
#define IEEE80211_WIDS_SPOOF_DISASSOC 0x02

#define IEEE80211_WIDS_WEAKIV_DETECT 0x03
/* end peiwenhui add 090625 --- for get attack detect info */
#define IEEE80211_STA_INTERFER_DETECT 0x09
#define IEEE80211_STA_INTERFER_CLEAR 0x0a

#ifdef VOW_LOGLATENCY
#define ATH_STATS_LATENCY_BINS 45  /* Number of 1024us bins to log latency */
#define ATH_STATS_LATENCY_CATS 5     /* Number of categories to log latency: 4 access categories + 1 combined */
#endif

#define ATH_STATS_VI_LOG_LEN 10


struct user_net_device_stats {
	unsigned long long rx_packets;	/* total packets received       */
	unsigned long long tx_packets;	/* total packets transmitted    */
	unsigned long long rx_bytes;	/* total bytes received         */
	unsigned long long tx_bytes;	/* total bytes transmitted      */
	unsigned long rx_errors;	/* bad packets received         */
	unsigned long tx_errors;	/* packet transmit problems     */
	unsigned long rx_dropped;	/* no space in linux buffers    */
	unsigned long tx_dropped;	/* no space available in linux  */
	unsigned long rx_multicast;	/* multicast packets received   */
	unsigned long rx_compressed;
	unsigned long tx_compressed;
	unsigned long collisions;
	unsigned long rx_broadcast;  /* pei add 090624 */
	unsigned long rx_unicast;
	unsigned long tx_multicast;
	unsigned long tx_broadcast;
	unsigned long tx_unicast;
	
	/* detailed rx_errors: */
	unsigned long rx_length_errors;
	unsigned long rx_over_errors;	/* receiver ring buff overflow  */
	unsigned long rx_crc_errors;	/* recved pkt with crc error    */
	unsigned long rx_frame_errors;	/* recv'd frame alignment error */
	unsigned long rx_fifo_errors;	/* recv'r fifo overrun          */
	unsigned long rx_missed_errors;	/* receiver missed packet     */
	/* detailed tx_errors */
	unsigned long tx_aborted_errors;
	unsigned long tx_carrier_errors;
	unsigned long tx_fifo_errors;
	unsigned long tx_heartbeat_errors;
	unsigned long tx_window_errors;
	unsigned long rx_multicast_bytes;
	unsigned long tx_multicast_bytes;
	unsigned long rx_broadcast_bytes;
	unsigned long tx_broadcast_bytes;
	unsigned long long rx_unicast_bytes;
	unsigned long long tx_unicast_bytes;
	unsigned long rx_retry_bytes;
	unsigned long tx_retry_bytes;
	unsigned long rx_retry;
	unsigned long tx_retry;	
	unsigned long rx_error_frames;		/* bad frames received		*/
};
//#ifdef NO_USE_MADWIFI
/*******************wireless_copy.h*****************************************/
#define SIOCIWFIRSTPRIV			0x8BE0

/*******************ieee80211_crypto.h**************************************/
/*
 * NB: these values are ordered carefully; there are lots of
 * of implications in any reordering.  In particular beware
 * that 4 is not used to avoid conflicting with IEEE80211_F_PRIVACY.
 */
 
/*
 * 802.11 protocol crypto-related definitions.
 */
#define	IEEE80211_KEYBUF_SIZE	16
#define	IEEE80211_MICBUF_SIZE	(8 + 8)		/* space for both TX & RX keys */
#define	IEEE80211_TID_SIZE		17		/* total number of TIDs */

/*
 * Old WEP-style key.  Deprecated.
 */
struct ieee80211_wepkey {
	u_int wk_len;				/* key length in bytes */
	u_int8_t wk_key[IEEE80211_KEYBUF_SIZE];
};
typedef u_int16_t ieee80211_keyix_t;
struct ieee80211_key {
	u_int8_t wk_keylen;		/* key length in bytes */
	u_int8_t wk_flags;
#define	IEEE80211_KEY_XMIT	0x01	/* key used for xmit */
#define	IEEE80211_KEY_RECV	0x02	/* key used for recv */
#define	IEEE80211_KEY_GROUP	0x04	/* key used for WPA group operation */
#define	IEEE80211_KEY_SWCRYPT	0x10	/* host-based encrypt/decrypt */
#define	IEEE80211_KEY_SWMIC	0x20	/* host-based enmic/demic */
	ieee80211_keyix_t wk_keyix;	/* key index */
	u_int8_t wk_key[IEEE80211_KEYBUF_SIZE+IEEE80211_MICBUF_SIZE];
#define	wk_txmic	wk_key+IEEE80211_KEYBUF_SIZE+0	/* XXX can't () right */
#define	wk_rxmic	wk_key+IEEE80211_KEYBUF_SIZE+8	/* XXX can't () right */
	u_int64_c wk_keyrsc[IEEE80211_TID_SIZE];	/* key receive sequence counter */
	u_int64_c wk_keytsc;		/* key transmit sequence counter */
	const struct ieee80211_cipher *wk_cipher;
	void *wk_private;		/* private cipher state */
};
#define	IEEE80211_KEY_COMMON 		/* common flags passed in by apps */\
	(IEEE80211_KEY_XMIT | IEEE80211_KEY_RECV | IEEE80211_KEY_GROUP)

#define	IEEE80211_CIPHER_WEP		0
#define	IEEE80211_CIPHER_TKIP		1
#define	IEEE80211_CIPHER_AES_OCB	2
#define	IEEE80211_CIPHER_AES_CCM	3
#define	IEEE80211_CIPHER_CKIP		5
#define	IEEE80211_CIPHER_NONE		6	/* pseudo value */

#define	IEEE80211_CIPHER_MAX		(IEEE80211_CIPHER_NONE + 1)

#define	IEEE80211_KEYIX_NONE	((ieee80211_keyix_t) -1)

/*******************ieee80211.h**************************************/
#define	IEEE80211_NWID_LEN			32

#define	WPA_OUI			0xf25000
#define	WPA_OUI_TYPE		0x01

#define	IEEE80211_ADDR_LEN	6
#define	IEEE80211_RATE_VAL		0x7f

#define	IEEE80211_CAPINFO_ESS			0x0001
#define	IEEE80211_CAPINFO_IBSS			0x0002
#define	IEEE80211_CAPINFO_CF_POLLABLE		0x0004
#define	IEEE80211_CAPINFO_CF_POLLREQ		0x0008
#define	IEEE80211_CAPINFO_PRIVACY		0x0010
#define	IEEE80211_CAPINFO_SHORT_PREAMBLE	0x0020
#define	IEEE80211_CAPINFO_PBCC			0x0040
#define	IEEE80211_CAPINFO_CHNL_AGILITY		0x0080
/* bits 8-9 are reserved (8 now for specturm management) */
#define IEEE80211_CAPINFO_SPECTRUM_MGMT		0x0100
#define	IEEE80211_CAPINFO_SHORT_SLOTTIME	0x0400
#define	IEEE80211_CAPINFO_RSN			0x0800
/* bit 12 is reserved */
#define	IEEE80211_CAPINFO_DSSSOFDM		0x2000
/* bits 14-15 are reserved */

/*
 * Management information element payloads.
 */
enum {
	IEEE80211_ELEMID_SSID		= 0,
	IEEE80211_ELEMID_RATES		= 1,
	IEEE80211_ELEMID_FHPARMS	= 2,
	IEEE80211_ELEMID_DSPARMS	= 3,
	IEEE80211_ELEMID_CFPARMS	= 4,
	IEEE80211_ELEMID_TIM		= 5,
	IEEE80211_ELEMID_IBSSPARMS	= 6,
	IEEE80211_ELEMID_COUNTRY	= 7,
	IEEE80211_ELEMID_HOPPATRNPARMS  = 8,
	IEEE80211_ELEMID_HOPPATRNTABLE  = 9,
	IEEE80211_ELEMID_REQINFO	= 10,
	IEEE80211_ELEMID_QBSSLOAD       = 11,
	IEEE80211_ELEMID_EDCAPARAM      = 12,
	IEEE80211_ELEMID_TSPEC		= 13,
	IEEE80211_ELEMID_TRAFCLASS      = 14,
	IEEE80211_ELEMID_SCHEDULE       = 15,
	IEEE80211_ELEMID_CHALLENGE	= 16,
	/* 17-31 reserved for challenge text extension */
	IEEE80211_ELEMID_PWRCNSTR	= 32,
	IEEE80211_ELEMID_PWRCAP		= 33,
	IEEE80211_ELEMID_TPCREQ		= 34,
	IEEE80211_ELEMID_TPCREP		= 35,
	IEEE80211_ELEMID_SUPPCHAN	= 36,
	IEEE80211_ELEMID_CHANSWITCHANN	= 37,
	IEEE80211_ELEMID_MEASREQ	= 38,
	IEEE80211_ELEMID_MEASREP	= 39,
	IEEE80211_ELEMID_QUIET		= 40,
	IEEE80211_ELEMID_IBSSDFS	= 41,
	IEEE80211_ELEMID_ERP		= 42,
	IEEE80211_ELEMID_TSDELAY	= 43,
	IEEE80211_ELEMID_TCLASSPROC     = 44,
	IEEE80211_ELEMID_QOS		= 46,
	IEEE80211_ELEMID_RSN		= 48,
	/* 49 reserved */
	IEEE80211_ELEMID_XRATES		= 50,
	/*ljy--add begin for wapi*/
	IEEE80211_ELEMID_WAPI		= 68,
	/*ljy--add end*/
	/* 128-129 proprietary elements used by Agere chipsets */
	IEEE80211_ELEMID_AGERE1		= 128,
	IEEE80211_ELEMID_AGERE2		= 129,
	IEEE80211_ELEMID_TPC		= 150,
	IEEE80211_ELEMID_CCKM		= 156,
	IEEE80211_ELEMID_VENDOR		= 221,	/* vendor private */
};
/*******************_ieee80211.h**************************************/

#define	IEEE80211_RATE_MAXSIZE	36

/* * Authentication mode. */
enum ieee80211_authmode {
	IEEE80211_AUTH_NONE	= 0,	
	IEEE80211_AUTH_OPEN	= 1,		/* open */
	IEEE80211_AUTH_SHARED	= 2,		/* shared-key */	
	IEEE80211_AUTH_8021X	= 3,		/* 802.1x */	
	IEEE80211_AUTH_AUTO	= 4,		/* auto-select/accept */
	/* NB: these are used only for ioctls */
	IEEE80211_AUTH_WPA	= 5,	
	/* WPA/RSN w/ 802.1x/PSK */
};
enum ieee80211_opmode {
	IEEE80211_M_STA		= 1,	/* infrastructure station */
	IEEE80211_M_IBSS 	= 0,	/* IBSS (adhoc) station */
	IEEE80211_M_AHDEMO	= 3,	/* Old lucent compatible adhoc demo */
	IEEE80211_M_HOSTAP	= 6,	/* Software Access Point */
	IEEE80211_M_MONITOR	= 8,	/* Monitor mode */
	IEEE80211_M_WDS		= 2	/* WDS link */
};
/*******************if_athioctl.h**************************************/
#ifdef __linux__
#define	SIOCGATHSTATS	(SIOCDEVPRIVATE+0)
#define	SIOCGATHDIAG	(SIOCDEVPRIVATE+1)
#define SIOCGATHRADARSIG (SIOCDEVPRIVATE+2)
//#else
//#define	SIOCGATHSTATS	_IOWR('i', 137, struct ifreq)
//#define	SIOCGATHDIAG	_IOWR('i', 138, struct ath_diag)
#endif

struct ath_11n_stats {
    u_int32_t   tx_pkts;            /* total tx data packets */
    u_int32_t   tx_checks;          /* tx drops in wrong state */
    u_int32_t   tx_drops;           /* tx drops due to qdepth limit */
    u_int32_t   tx_minqdepth;       /* tx when h/w queue depth is low */
    u_int32_t   tx_queue;           /* tx pkts when h/w queue is busy */
    u_int32_t   tx_resetq;          /* tx reset queue instances */
    u_int32_t   tx_comps;           /* tx completions */
    u_int32_t   tx_comperror;       /* tx error completions on global failures */
    u_int32_t   tx_unaggr_comperror; /* tx error completions of unaggregted frames */
    u_int32_t   tx_stopfiltered;    /* tx pkts filtered for requeueing */
    u_int32_t   tx_qnull;           /* txq empty occurences */
    u_int32_t   tx_noskbs;          /* tx no skbs for encapsulations */
    u_int32_t   tx_nobufs;          /* tx no descriptors */
    u_int32_t   tx_badsetups;       /* tx key setup failures */
    u_int32_t   tx_normnobufs;      /* tx no desc for legacy packets */
    u_int32_t   tx_schednone;       /* tx schedule pkt queue empty */
    u_int32_t   tx_bars;            /* tx bars sent */
    u_int32_t   tx_legacy;          /* tx legacy frames sent */
    u_int32_t   txunaggr_single;    /* tx unaggregate singles sent */
    u_int32_t   txbar_xretry;       /* tx bars excessively retried */
    u_int32_t   txbar_compretries;  /* tx bars retried */
    u_int32_t   txbar_errlast;      /* tx bars last frame failed */
    u_int32_t   tx_compunaggr;      /* tx unaggregated frame completions */
    u_int32_t   txunaggr_xretry;    /* tx unaggregated excessive retries */
    u_int32_t   tx_compaggr;        /* tx aggregated completions */
    u_int32_t   tx_bawadv;          /* tx block ack window advanced */
    u_int32_t   tx_bawretries;      /* tx block ack window retries */
    u_int32_t   tx_bawnorm;         /* tx block ack window additions */
    u_int32_t   tx_bawupdates;      /* tx block ack window updates */
    u_int32_t   tx_bawupdtadv;      /* tx block ack window advances */
    u_int32_t   tx_retries;         /* tx retries of sub frames */
    u_int32_t   tx_xretries;        /* tx excessive retries of aggregates */
    u_int32_t   tx_aggregates;      /* tx aggregated pkts sent */
    u_int32_t   tx_sf_hw_xretries;  /* sub-frames excessively retried in h/w */
    u_int32_t   tx_aggr_frames;     /* tx total frames aggregated */
    u_int32_t   txaggr_noskbs;      /* tx no skbs for aggr encapsualtion */
    u_int32_t   txaggr_nobufs;      /* tx no desc for aggr */
    u_int32_t   txaggr_badkeys;     /* tx enc key setup failures */
    u_int32_t   txaggr_schedwindow; /* tx no frame scheduled: baw limited */
    u_int32_t   txaggr_single;      /* tx frames not aggregated */
    u_int32_t   txaggr_mimo;        /* tx frames aggregated for mimo */
    u_int32_t   txaggr_compgood;    /* tx aggr good completions */
    u_int32_t   txaggr_comperror;   /* tx aggr error completions */
    u_int32_t   txaggr_compxretry;  /* tx aggr excessive retries */
    u_int32_t   txaggr_compretries; /* tx aggr unacked subframes */
    u_int32_t   txunaggr_compretries; /* tx non-aggr unacked subframes */
    u_int32_t   txaggr_prepends;    /* tx aggr old frames requeued */
    u_int32_t   txaggr_filtered;    /* filtered aggr packet */
    u_int32_t   txaggr_fifo;        /* fifo underrun of aggregate */
    u_int32_t   txaggr_xtxop;       /* txop exceeded for an aggregate */
    u_int32_t   txaggr_desc_cfgerr; /* aggregate descriptor config error */
    u_int32_t   txaggr_data_urun;   /* data underrun for an aggregate */
    u_int32_t   txaggr_delim_urun;  /* delimiter underrun for an aggregate */
    u_int32_t   txaggr_errlast;     /* tx aggr: last sub-frame failed */
    u_int32_t   txunaggr_errlast;   /* tx non-aggr: last frame failed */
    u_int32_t   txaggr_longretries; /* tx aggr h/w long retries */
    u_int32_t   txaggr_shortretries;/* tx aggr h/w short retries */
    u_int32_t   txaggr_timer_exp;   /* tx aggr : tx timer expired */
    u_int32_t   txaggr_babug;       /* tx aggr : BA bug */
    u_int32_t   txrifs_single;      /* tx frames not bursted */
    u_int32_t   txrifs_babug;       /* tx rifs : BA bug */
    u_int32_t   txaggr_badtid;      /* tx aggr : Bad TID */
    u_int32_t   txrifs_compretries; /* tx rifs unacked subframes */
    u_int32_t   txrifs_bar_alloc;   /* tx rifs bars allocated */
    u_int32_t   txrifs_bar_freed;   /* tx rifs bars freed */
    u_int32_t   txrifs_compgood;    /* tx rifs good completions */
    u_int32_t   txrifs_prepends;    /* tx rifs old frames requeued */
    u_int32_t   tx_comprifs;        /* tx rifs completions */
    u_int32_t   tx_compnorifs;      /* tx not a rifs completion */
    u_int32_t   rx_pkts;            /* rx pkts */
    u_int32_t   rx_aggr;            /* rx aggregated packets */
    u_int32_t   rx_aggrbadver;      /* rx pkts with bad version */
    u_int32_t   rx_bars;            /* rx bars */
    u_int32_t   rx_nonqos;          /* rx non qos-data frames */
    u_int32_t   rx_seqreset;        /* rx sequence resets */
    u_int32_t   rx_oldseq;          /* rx old packets */
    u_int32_t   rx_bareset;         /* rx block ack window reset */
    u_int32_t   rx_baresetpkts;     /* rx pts indicated due to baw resets */
    u_int32_t   rx_dup;             /* rx duplicate pkts */
    u_int32_t   rx_baadvance;       /* rx block ack window advanced */
    u_int32_t   rx_recvcomp;        /* rx pkt completions */
    u_int32_t   rx_bardiscard;      /* rx bar discarded */
    u_int32_t   rx_barcomps;        /* rx pkts unblocked on bar reception */
    u_int32_t   rx_barrecvs;        /* rx pkt completions on bar reception */
    u_int32_t   rx_skipped;         /* rx pkt sequences skipped on timeout */
    u_int32_t   rx_comp_to;         /* rx indications due to timeout */
    u_int32_t   rx_timer_starts;    /* rx countdown timers started */
    u_int32_t   rx_timer_stops;     /* rx countdown timers stopped */ 
    u_int32_t   rx_timer_run;       /* rx timeout occurences */
    u_int32_t   rx_timer_more;      /* rx partial timeout of pending packets */
    u_int32_t   wd_tx_active;       /* watchdog: tx is active */
    u_int32_t   wd_tx_inactive;     /* watchdog: tx is not active */
    u_int32_t   wd_tx_hung;         /* watchdog: tx is hung */
    u_int32_t   wd_spurious;        /* watchdog: spurious tx hang */
    u_int32_t   tx_requeue;         /* filter & requeue on 20/40 transitions */
    u_int32_t   tx_drain_txq;       /* draining tx queue on error */
    u_int32_t   tx_drain_tid;       /* draining tid buf queue on error */
    u_int32_t   tx_cleanup_tid;     /* draining tid buf queue on node cleanup */
    u_int32_t   tx_drain_bufs;      /* buffers drained from pending tid queue */
    u_int32_t   tx_tidpaused;       /* pausing tx on tid */
    u_int32_t   tx_tidresumed;      /* resuming tx on tid */
    u_int32_t   tx_unaggr_filtered; /* unaggregated tx pkts filtered */
    u_int32_t   tx_aggr_filtered;   /* aggregated tx pkts filtered */
    u_int32_t   tx_filtered;        /* total sub-frames filtered */
    u_int32_t   rx_rb_on;           /* total rb-s on  */
    u_int32_t   rx_rb_off;          /* total rb-s off */
    u_int32_t   rx_dsstat_err;      /* rx descriptor status corrupted */
    u_int32_t   bf_stream_miss;     /* beamform stream mismatch */ 
    u_int32_t   bf_bandwidth_miss;  /* beamform bandwidth mismatch */ 
    u_int32_t   bf_destination_miss;/* beamform destination mismatch */ 

};

#define MAX_BB_PANICS 3
struct ath_bb_panic_info {
    int valid;
    u_int32_t status;
    u_int32_t tsf;
    u_int32_t phy_panic_wd_ctl1;
    u_int32_t phy_panic_wd_ctl2;
    u_int32_t phy_gen_ctrl;
    u_int32_t rxc_pcnt;
    u_int32_t rxf_pcnt;
    u_int32_t txf_pcnt;
    u_int32_t cycles;
    u_int32_t wd;
    u_int32_t det;
    u_int32_t rdar;
    u_int32_t rODFM;
    u_int32_t rCCK;
    u_int32_t tODFM;
    u_int32_t tCCK;
    u_int32_t agc;
    u_int32_t src;
};

/*Begin:Added by duanmingzhe for print txq info*/
struct txqinfo
{
	u_int32_t txq_headindex;
	u_int32_t txq_tailindex;
	u_int32_t txq_depth;
	u_int32_t txq_minfree;
	u_int32_t txq_num_buf_used;
	u_int32_t txq_aggr_depth;
	u_int32_t txq_totalqueued;
	u_int32_t txq_intrcnt;
};
/*End:Added by duanmingzhe for print txq info*/

#define ATH_SUPPORT_TxBF
#define ATH_SUPPORT_UAPSD

struct ath_stats {
    u_int32_t    ast_watchdog;     /* device reset by watchdog */
    u_int32_t    ast_resetOnError; /* resets on error */
	/*Begin:Added by duanmingzhe for tx interrupt count*/
	u_int32_t    ast_isr_txok_wifi0_count;
	u_int32_t    ast_isr_txerr_wifi0_count;
	u_int32_t    ast_isr_txeol_wifi0_count;	
	u_int32_t    ast_isr_txok_wifi1_count;
	u_int32_t    ast_isr_txerr_wifi1_count;
	u_int32_t    ast_isr_txeol_wifi1_count;
	/*End:Added by duanmingzhe for tx interrupt count*/

	
	/*Begin:Added by duanmingzhe for print txq info*/
	struct txqinfo ast_qcu_info_wifi0[10];
	struct txqinfo ast_qcu_info_wifi1[10];	
	/*End:Added by duanmingzhe for print txq info*/
    u_int32_t    ast_hardware;     /* fatal hardware error interrupts */
    u_int32_t    ast_bmiss;        /* beacon miss interrupts */
    u_int32_t    ast_rxorn;        /* rx overrun interrupts */
    u_int32_t    ast_rxorn_bmiss;  /* rx overrun and bmiss interrupts: indicate descriptor corruption */
    u_int32_t    ast_rxeol;        /* rx eol interrupts */
    u_int32_t    ast_txurn;        /* tx underrun interrupts */
    u_int32_t    ast_txto;         /* tx timeout interrupts */
    u_int32_t    ast_cst;          /* carrier sense timeout interrupts */
    u_int32_t    ast_mib;          /* mib interrupts */
    u_int32_t    ast_rx;           /* rx interrupts */
    u_int32_t    ast_rxdesc;       /* rx descriptor interrupts */
    u_int32_t    ast_rxerr;        /* rx error interrupts */
    u_int32_t    ast_rxnofrm;      /* rx no frame interrupts */
    u_int32_t    ast_tx;           /* tx interrupts */
    u_int32_t    ast_txdesc;       /* tx descriptor interrupts */
    u_int32_t    ast_tim_timer;    /* tim timer interrupts */
    u_int32_t    ast_bbevent;      /* baseband event interrupts */
    u_int32_t    ast_rxphy;        /* rx phy error interrupts */
    u_int32_t    ast_rxkcm;        /* rx key cache miss interrupts */
    u_int32_t    ast_swba;         /* sw beacon alert interrupts */
    u_int32_t    ast_bnr;          /* beacon not ready interrupts */
    u_int32_t    ast_tim;          /* tim interrupts */
    u_int32_t    ast_dtim;         /* dtim interrupts */
    u_int32_t    ast_dtimsync;     /* dtimsync interrupts */
    u_int32_t    ast_gpio;         /* general purpose IO interrupts */
    u_int32_t    ast_cabend;       /* cab end interrupts */
    u_int32_t    ast_tsfoor;       /* tsf out-of-range interrupts */
    u_int32_t    ast_gentimer;     /* generic timer interrupts */
    u_int32_t    ast_gtt;          /* global transmit timeout interrupts */
    u_int32_t    ast_fatal;        /* fatal interrupts */
    u_int32_t    ast_tx_packets;   /* packet sent on the interface */
    u_int32_t    ast_rx_packets;   /* packet received on the interface */
    u_int32_t    ast_tx_mgmt;      /* management frames transmitted */
    u_int32_t    ast_tx_discard;   /* frames discarded prior to assoc */
    u_int32_t    ast_tx_invalid;   /* frames discarded 'cuz device gone */
    u_int32_t    ast_tx_qstop;     /* tx queue stopped 'cuz full */
    u_int32_t    ast_tx_encap;     /* tx encapsulation failed */
    u_int32_t    ast_tx_nonode;    /* tx failed 'cuz no node */
    u_int32_t    ast_tx_nobuf;     /* tx failed 'cuz no tx buffer (data) */
    u_int32_t    ast_tx_stop;      /* number of times the netif_stop called*/
    u_int32_t    ast_tx_resume;    /* number of times netif_wake_queue called */
    u_int32_t    ast_tx_nobufmgt;  /* tx failed 'cuz no tx buffer (mgmt)*/
    u_int32_t    ast_tx_xretries;  /* tx failed 'cuz too many retries */
    u_int32_t    ast_tx_fifoerr;   /* tx failed 'cuz FIFO underrun */
    u_int32_t    ast_tx_filtered;  /* tx failed 'cuz xmit filtered */
    u_int32_t    ast_tx_badrate;   /* tx failed 'cuz bogus xmit rate */
    u_int32_t    ast_tx_noack;     /* tx frames with no ack marked */
    u_int32_t    ast_tx_cts;       /* tx frames with cts enabled */
    u_int32_t    ast_tx_shortpre;  /* tx frames with short preamble */
    u_int32_t    ast_tx_altrate;   /* tx frames with alternate rate */
    u_int32_t    ast_tx_protect;   /* tx frames with protection */
    u_int32_t    ast_rx_orn;       /* rx failed 'cuz of desc overrun */
    u_int32_t    ast_rx_badcrypt;  /* rx failed 'cuz decryption */
    u_int32_t    ast_rx_badmic;    /* rx failed 'cuz MIC failure */
    u_int32_t    ast_rx_nobuf;     /* rx setup failed 'cuz no skbuff */
        u_int32_t       ast_rx_hal_in_progress;
        u_int32_t       ast_rx_num_data;
        u_int32_t       ast_rx_num_mgmt;
        u_int32_t       ast_rx_num_ctl;
        u_int32_t       ast_rx_num_unknown;
        u_int32_t       ast_max_pkts_per_intr;
#define ATH_STATS_MAX_INTR_BKT  512
    u_int32_t   ast_pkts_per_intr[ATH_STATS_MAX_INTR_BKT+1]; /* counter bucket of packets handled in a single iteration */
    int8_t      ast_tx_rssi;                    /* tx rssi of last ack */
    int8_t      ast_tx_rssi_ctl0;               /* tx rssi of last ack [ctl, chain 0] */
    int8_t      ast_tx_rssi_ctl1;               /* tx rssi of last ack [ctl, chain 1] */
    int8_t      ast_tx_rssi_ctl2;               /* tx rssi of last ack [ctl, chain 2] */
    int8_t      ast_tx_rssi_ext0;               /* tx rssi of last ack [ext, chain 0] */
    int8_t      ast_tx_rssi_ext1;               /* tx rssi of last ack [ext, chain 1] */
    int8_t      ast_tx_rssi_ext2;               /* tx rssi of last ack [ext, chain 2] */
    int8_t      ast_rx_rssi;                    /* rx rssi from histogram [combined]*/
    int8_t      ast_rx_rssi_ctl0;               /* rx rssi from histogram [ctl, chain 0] */
    int8_t      ast_rx_rssi_ctl1;               /* rx rssi from histogram [ctl, chain 1] */
    int8_t      ast_rx_rssi_ctl2;               /* rx rssi from histogram [ctl, chain 2] */
    int8_t      ast_rx_rssi_ext0;               /* rx rssi from histogram [ext, chain 0] */
    int8_t      ast_rx_rssi_ext1;               /* rx rssi from histogram [ext, chain 1] */
    int8_t      ast_rx_rssi_ext2;               /* rx rssi from histogram [ext, chain 2] */
    u_int32_t   ast_be_xmit;                    /* beacons transmitted */
    u_int32_t   ast_be_nobuf;                    /* no skbuff available for beacon */
    u_int32_t   ast_per_cal;                    /* periodic calibration calls */
    u_int32_t   ast_per_calfail;                /* periodic calibration failed */
    u_int32_t   ast_per_rfgain;                    /* periodic calibration rfgain reset */
    u_int32_t   ast_rate_calls;                    /* rate control checks */
    u_int32_t   ast_rate_raise;                    /* rate control raised xmit rate */
    u_int32_t   ast_rate_drop;                    /* rate control dropped xmit rate */
    u_int32_t   ast_ant_defswitch;              /* rx/default antenna switches */
    u_int32_t   ast_ant_txswitch;               /* tx antenna switches */
	/*zhaoyang1 transplant from 717*/
	/*pengruofeng add for wifi stats 2011-5-9*/
	u_int32_t	ast_up_times;	/* wifi up times.*/
 	u_int32_t	ast_down_times;	/* wifi down times.*/
	u_int32_t   ast_rx_phyerr;	/* rx PHY error summary count */
	u_int32_t   ast_rx_crcerr;	/* rx failed 'cuz of bad CRC */
	u_int32_t   ast_rx_mgt;
	/*pengruofeng add end 2011-5-9*/
	/*zhaoyang1 transplant end*/
    u_int32_t   ast_ant_rx[8];                    /* rx frames with antenna */
    u_int32_t   ast_ant_tx[8];                    /* tx frames with antenna */
    u_int64_c   ast_rx_bytes;                    /* total number of bytes received */
    u_int64_c   ast_tx_bytes;                    /* total number of bytes transmitted */
    u_int32_t   ast_rx_num_qos_data[16];        /* per tid rx packets (includes duplicates)*/
    u_int32_t   ast_rx_num_nonqos_data;         /* non qos rx packets    */
    u_int32_t   ast_txq_packets[16];            /* perq aggr packets sent on the interface for each category */
    u_int32_t   ast_txq_noaggr_packets[16];     /* perq no-aggr packets sent on the interface for each category */
    u_int32_t   ast_txq_xretries[16];           /* per q tx failed 'cuz too many retries */
    u_int32_t   ast_txq_fifoerr[16];            /* per q tx failed 'cuz FIFO underrun */
    u_int32_t   ast_txq_filtered[16];           /*per q  tx failed 'cuz xmit filtered */
    u_int32_t   ast_txq_athbuf_limit[16];       /* tx dropped 'cuz of athbuf limit */
    u_int32_t   ast_txq_nobuf[16];              /* tx dropped 'cuz no athbufs */
    u_int8_t    ast_num_rxchain;                /* Number of rx chains */
    u_int8_t    ast_num_txchain;                /* Number of tx chains */
    struct ath_11n_stats ast_11n_stats;         /* 11n statistics */
    u_int32_t   ast_bb_hang;                    /* BB hang detected */
    u_int32_t   ast_mac_hang;                   /* MAC hang detected */
#if ATH_WOW
    u_int32_t   ast_wow_wakeups;                /* count of hibernate and standby wakeups */
    u_int32_t   ast_wow_wakeupsok;              /* count of wakeups thru WoW */
    u_int32_t   ast_wow_wakeupserror;           /* count of errored wakeups */
#if ATH_WOW_DEBUG
    u_int32_t   ast_normal_sleeps;              /* count of normal sleeps */
    u_int32_t   ast_normal_wakeups;             /* count of normal wakeups*/
    u_int32_t   ast_wow_sleeps;                 /* count of wow sleeps */
    u_int32_t   ast_wow_sleeps_nonet;           /* w/o IP config */
#endif
#endif
#ifdef ATH_SUPPORT_UAPSD
    u_int32_t   ast_uapsdqnulbf_unavail;        /* no qos null buffers available */
    u_int32_t   ast_uapsdqnul_pkts;             /* count of qos null frames sent */
    u_int32_t   ast_uapsdtriggers;              /* count of UAPSD triggers received */
    u_int32_t   ast_uapsdnodeinvalid;           /* count of triggers for non-UAPSD node */
    u_int32_t   ast_uapsdeospdata;              /* count of QoS Data with EOSP sent */
    u_int32_t   ast_uapsddata_pkts;             /* count of UAPSD QoS Data frames sent */
    u_int32_t   ast_uapsddatacomp;              /* count of UAPSD QoS Data frames completed */
    u_int32_t   ast_uapsdqnulcomp;              /* count of UAPSD QoS NULL frames completed */
    u_int32_t   ast_uapsddataqueued;            /* count of UAPSD QoS Data Queued */
#endif
#ifdef ATH_SUPPORT_VOWEXT
    /* VOWEXT stats only. Literally some of the iqueue stats can be re-used here
     * As part of current release, all vow stats will be added extra and 
     * re-using will be thought for next release 
     */
    /*
     * ast_vow_ul_tx_calls : Number of frames Upper Layer ( ieee ) tried to send
     * over each access category. For each of the AC this would denote how many 
     * frames reached ATH layer.
     *                       
     * ast_vow_ath_txq_calls: Subset of ( ast_vow_ul_tx_calls ) that can be
     * either queued or can be sent immediate, either as an aggregate or as an
     * normal frame. This counts only frames that can be sent. 
    */
    u_int32_t   ast_vow_ul_tx_calls[4]; 
    u_int32_t   ast_vow_ath_txq_calls[4];
    u_int32_t   ast_vow_ath_be_drop, ast_vow_ath_bk_drop;
#endif
#if ATH_SUPPORT_CFEND
    u_int32_t ast_cfend_sched;			/* count of CF-END frames scheduled */
    u_int32_t ast_cfend_sent;   		/* count of CF-END frames sent */
#endif
#ifdef VOW_LOGLATENCY
    u_int32_t ast_retry_delay[ATH_STATS_LATENCY_CATS][ATH_STATS_LATENCY_BINS];
    u_int32_t ast_queue_delay[ATH_STATS_LATENCY_CATS][ATH_STATS_LATENCY_BINS];
#endif

#if UMAC_SUPPORT_VI_DBG
    u_int32_t   vi_timestamp[ATH_STATS_VI_LOG_LEN];      /* h/w assigned timestamp        */
    u_int8_t    vi_rssi_ctl0[ATH_STATS_VI_LOG_LEN];      /* rx frame RSSI [ctl, chain 0]  */
    u_int8_t    vi_rssi_ctl1[ATH_STATS_VI_LOG_LEN];      /* rx frame RSSI [ctl, chain 1]  */
    u_int8_t    vi_rssi_ctl2[ATH_STATS_VI_LOG_LEN];      /* rx frame RSSI [ctl, chain 2]  */
    u_int8_t    vi_rssi_ext0[ATH_STATS_VI_LOG_LEN];      /* rx frame RSSI [ext, chain 0]  */
    u_int8_t    vi_rssi_ext1[ATH_STATS_VI_LOG_LEN];      /* rx frame RSSI [ext, chain 1]  */
    u_int8_t    vi_rssi_ext2[ATH_STATS_VI_LOG_LEN];      /* rx frame RSSI [ext, chain 2]  */
    u_int8_t    vi_rssi[ATH_STATS_VI_LOG_LEN];
    u_int8_t    vi_evm0[ATH_STATS_VI_LOG_LEN];           /* evm - chain 0                 */
    u_int8_t    vi_evm1[ATH_STATS_VI_LOG_LEN];           /* evm - chain 1                 */
    u_int8_t    vi_evm2[ATH_STATS_VI_LOG_LEN];           /* evm - chain 2                 */
    u_int8_t    vi_rs_rate[ATH_STATS_VI_LOG_LEN];        /* h/w receive rate index        */
    u_int32_t   vi_tx_frame_cnt[ATH_STATS_VI_LOG_LEN];   /* Profile count transmit frames */
    u_int32_t   vi_rx_frame_cnt[ATH_STATS_VI_LOG_LEN];   /* Profile count receive frames  */
    u_int32_t   vi_rx_clr_cnt[ATH_STATS_VI_LOG_LEN];     /* Profile count receive clear   */
    u_int32_t   vi_rx_ext_clr_cnt[ATH_STATS_VI_LOG_LEN]; /* Profile count receive clear on ext channel */
    u_int32_t   vi_cycle_cnt[ATH_STATS_VI_LOG_LEN];      /* Profile count cycle counter   */
    u_int8_t    vi_stats_index;                          /* Used to index circular buffer used to hold video stats */
#endif
#ifdef ATH_SUPPORT_TxBF
#define MCS_RATE 0x1f
    u_int8_t    ast_txbf;
    u_int8_t    ast_lastratecode;
    u_int32_t   ast_sounding_count;
    u_int32_t   ast_txbf_rpt_count;
    u_int32_t   ast_mcs_count[MCS_RATE+1];
#endif
    struct ath_bb_panic_info ast_bb_panic[MAX_BB_PANICS];
};

/*******************ieee80211_ioctl.h**************************************/
#define	SIOCG80211STATS				(SIOCDEVPRIVATE+2)
#define	IEEE80211_IOCTL_GETKEY		(SIOCDEVPRIVATE+3)
#define	IEEE80211_IOCTL_GETWPAIE		(SIOCDEVPRIVATE+4)
#define	IEEE80211_IOCTL_STA_STATS	(SIOCDEVPRIVATE+5)
#define	IEEE80211_IOCTL_STA_INFO		(SIOCDEVPRIVATE+6)
#define	SIOC80211IFCREATE				(SIOCDEVPRIVATE+7)
#define	SIOC80211IFDESTROY			(SIOCDEVPRIVATE+8)
#define	IEEE80211_IOCTL_SCAN_RESULTS	(SIOCDEVPRIVATE+9)
/*
 * WPA/RSN get/set key request.  Specify the key/cipher
 * type and whether the key is to be used for sending and/or
 * receiving.  The key index should be set only when working
 * with global keys (use IEEE80211_KEYIX_NONE for ``no index'').
 * Otherwise a unicast/pairwise key is specified by the bssid
 * (on a station) or mac address (on an ap).  They key length
 * must include any MIC key data; otherwise it should be no
 more than IEEE80211_KEYBUF_SIZE.
 */
struct ieee80211req_key {
	u_int8_t ik_type;		/* key/cipher type */
	u_int8_t ik_pad;
	ieee80211_keyix_t ik_keyix;	/* key index */
	u_int8_t ik_keylen;		/* key length in bytes */
	u_int8_t ik_flags;
/* NB: IEEE80211_KEY_XMIT and IEEE80211_KEY_RECV defined elsewhere */
#define	IEEE80211_KEY_DEFAULT	0x80	/* default xmit key */
	u_int8_t ik_macaddr[MAC_ADDR_LEN];
	u_int64_c ik_keyrsc;		/* key receive sequence counter */
	u_int64_c ik_keytsc;		/* key transmit sequence counter */
	u_int8_t ik_keydata[IEEE80211_KEYBUF_SIZE+IEEE80211_MICBUF_SIZE];
};

/*
 * Delete a key either by index or address.  Set the index
 * to IEEE80211_KEYIX_NONE when deleting a unicast key.
 */
struct ieee80211req_del_key {
	/* XXX: This should be ieee80211_keyix_t, but it changes API/ABI for hostapd */
	u_int8_t idk_keyix;	/* key index */
	u_int8_t idk_macaddr[MAC_ADDR_LEN];
};
struct ieee80211_clone_params {
	char icp_name[IFNAMSIZ];		/* device name */
	u_int16_t icp_opmode;			/* operating mode */
	u_int16_t icp_flags;			/* see below */
#define	IEEE80211_CLONE_BSSID	0x0001		/* allocate unique mac/bssid */
#define	IEEE80211_NO_STABEACONS	0x0002		/* Do not setup the station beacon timers */
};
enum {
        IEEE80211_WMMPARAMS_CWMIN       = 1,
        IEEE80211_WMMPARAMS_CWMAX       = 2,
        IEEE80211_WMMPARAMS_AIFS        = 3,
        IEEE80211_WMMPARAMS_TXOPLIMIT   = 4,
        IEEE80211_WMMPARAMS_ACM         = 5,
        IEEE80211_WMMPARAMS_NOACKPOLICY = 6,
};

enum {
	IEEE80211_PARAM_TURBO			= 1,	/* turbo mode */
	IEEE80211_PARAM_MODE			= 2,	/* phy mode (11a, 11b, etc.) */
	IEEE80211_PARAM_AUTHMODE		= 3,	/* authentication mode */
	IEEE80211_PARAM_PROTMODE		= 4,	/* 802.11g protection */
	IEEE80211_PARAM_MCASTCIPHER		= 5,	/* multicast/default cipher */
	IEEE80211_PARAM_MCASTKEYLEN		= 6,	/* multicast key length */
	IEEE80211_PARAM_UCASTCIPHERS		= 7,	/* unicast cipher suites */
	IEEE80211_PARAM_UCASTCIPHER		= 8,	/* unicast cipher */
	IEEE80211_PARAM_UCASTKEYLEN		= 9,	/* unicast key length */
	IEEE80211_PARAM_WPA			= 10,	/* WPA mode (0,1,2) */
	IEEE80211_PARAM_ROAMING			= 12,	/* roaming mode */
	IEEE80211_PARAM_PRIVACY			= 13,	/* privacy invoked */
	IEEE80211_PARAM_COUNTERMEASURES		= 14,	/* WPA/TKIP countermeasures */
	IEEE80211_PARAM_DROPUNENCRYPTED		= 15,	/* discard unencrypted frames */
	IEEE80211_PARAM_DRIVER_CAPS		= 16,	/* driver capabilities */
	IEEE80211_PARAM_MACCMD			= 17,	/* MAC ACL operation */
	IEEE80211_PARAM_WMM			= 18,	/* WMM mode (on, off) */
	IEEE80211_PARAM_HIDESSID		= 19,	/* hide SSID mode (on, off) */
	IEEE80211_PARAM_APBRIDGE    		= 20,   /* AP inter-sta bridging */
	IEEE80211_PARAM_KEYMGTALGS		= 21,	/* key management algorithms */
	IEEE80211_PARAM_RSNCAPS			= 22,	/* RSN capabilities */
	IEEE80211_PARAM_INACT			= 23,	/* station inactivity timeout */
	IEEE80211_PARAM_INACT_AUTH		= 24,	/* station auth inact timeout */
	IEEE80211_PARAM_INACT_INIT		= 25,	/* station init inact timeout */
	IEEE80211_PARAM_ABOLT			= 26,	/* Atheros Adv. Capabilities */
	IEEE80211_PARAM_DTIM_PERIOD		= 28,	/* DTIM period (beacons) */
	IEEE80211_PARAM_BEACON_INTERVAL		= 29,	/* beacon interval (ms) */
	IEEE80211_PARAM_DOTH			= 30,	/* 11.h is on/off */
	IEEE80211_PARAM_PWRTARGET		= 31,	/* Current Channel Pwr Constraint */
	IEEE80211_PARAM_GENREASSOC		= 32,	/* Generate a reassociation request */
	IEEE80211_PARAM_COMPRESSION		= 33,	/* compression */
	IEEE80211_PARAM_FF			= 34,	/* fast frames support  */
	IEEE80211_PARAM_XR			= 35,	/* XR support */
	IEEE80211_PARAM_BURST			= 36,	/* burst mode */
	IEEE80211_PARAM_PUREG			= 37,	/* pure 11g (no 11b stations) */
	IEEE80211_PARAM_AR			= 38,	/* AR support */
	IEEE80211_PARAM_WDS			= 39,	/* Enable 4 address processing */
	IEEE80211_PARAM_BGSCAN			= 40,	/* bg scanning (on, off) */
	IEEE80211_PARAM_BGSCAN_IDLE		= 41,	/* bg scan idle threshold */
	IEEE80211_PARAM_BGSCAN_INTERVAL		= 42,	/* bg scan interval */
	IEEE80211_PARAM_MCAST_RATE		= 43,	/* Multicast Tx Rate */
	IEEE80211_PARAM_COVERAGE_CLASS		= 44,	/* coverage class */
	IEEE80211_PARAM_COUNTRY_IE		= 45,	/* enable country IE */
	IEEE80211_PARAM_SCANVALID		= 46,	/* scan cache valid threshold */
	IEEE80211_PARAM_ROAM_RSSI_11A		= 47,	/* rssi threshold in 11a */
	IEEE80211_PARAM_ROAM_RSSI_11B		= 48,	/* rssi threshold in 11b */
	IEEE80211_PARAM_ROAM_RSSI_11G		= 49,	/* rssi threshold in 11g */
	IEEE80211_PARAM_ROAM_RATE_11A		= 50,	/* tx rate threshold in 11a */
	IEEE80211_PARAM_ROAM_RATE_11B		= 51,	/* tx rate threshold in 11b */
	IEEE80211_PARAM_ROAM_RATE_11G		= 52,	/* tx rate threshold in 11g */
	IEEE80211_PARAM_UAPSDINFO		= 53,	/* value for qos info field */
	IEEE80211_PARAM_SLEEP			= 54,	/* force sleep/wake */
	IEEE80211_PARAM_QOSNULL			= 55,	/* force sleep/wake */
	IEEE80211_PARAM_PSPOLL			= 56,	/* force ps-poll generation (sta only) */
	IEEE80211_PARAM_EOSPDROP		= 57,	/* force uapsd EOSP drop (ap only) */
	IEEE80211_PARAM_MARKDFS			= 58,	/* mark a dfs interference channel when found */
	IEEE80211_PARAM_REGCLASS		= 59,	/* enable regclass ids in country IE */
	IEEE80211_PARAM_DROPUNENC_EAPOL		= 60,	/* drop unencrypted eapol frames */
 	IEEE80211_PARAM_SHPREAMBLE		= 61,	/* Short Preamble */
	IEEE80211_PARAM_DUMPREGS		= 62,   /* Pretty printed dump of Atheros hardware registers */
#ifdef CAVIUM_PLATFORM
	IEEE80211_PARAM_DOTH_ALGORITHM		= 63,	/* spectrum management algorithm */
	IEEE80211_PARAM_DOTH_MINCOM   		= 64,	/* minimum number of common channels */
	IEEE80211_PARAM_DOTH_SLCG		= 65,	/* permil of Stations Lost per Channel Gained */
	IEEE80211_PARAM_DOTH_SLDG		= 66,	/* permil of Stations Lost per rssi Db Gained */
	IEEE80211_PARAM_TXCONT			= 67,	/* continuous transmit mode (boolean) */
	IEEE80211_PARAM_TXCONT_RATE		= 68,	/* continuous transmit mode data rate (in mbit/sec) - will use closest match from current rate table */
	IEEE80211_PARAM_TXCONT_POWER		= 69,	/* power level in units of 0.5dBm */
	IEEE80211_PARAM_DFS_TESTMODE		= 70,	/* do not perform DFS actions (i.e. markng DFS and channel change on interference), just report them via debug. */
	IEEE80211_PARAM_DFS_CACTIME		= 71,	/* how long do we wait for chan availability
							   scans ?
							   FCC requires 60s, so that is the default. */
	IEEE80211_PARAM_DFS_EXCLPERIOD		= 72,	/* DFS no-occupancy limit - how long do we stay
							   off a channel once radar is detected?
							   FCC requires 30m, so that is the default. */
	IEEE80211_PARAM_BEACON_MISS_THRESH	= 73,	/* Beacon miss threshold (in beacons) */
	IEEE80211_PARAM_BEACON_MISS_THRESH_MS	= 74,	/* Beacon miss threshold (in ms) */
	IEEE80211_PARAM_MAXRATE			= 75,	/* Maximum rate (by table index) */
	IEEE80211_PARAM_MINRATE			= 76,	/* Maximum rate (by table index) */
	IEEE80211_PARAM_PROTMODE_RSSI		= 77,	/* RSSI Threshold for enabling protection mode */
	IEEE80211_PARAM_PROTMODE_TIMEOUT	= 78,	/* Timeout for expiring protection mode */
	IEEE80211_PARAM_BGSCAN_THRESH		= 79,	/* bg scan rssi threshold */
	IEEE80211_PARAM_RSSI_DIS_THR	= 80,	/* rssi threshold for disconnection */
	IEEE80211_PARAM_RSSI_DIS_COUNT	= 81,	/* counter for rssi threshold */
	IEEE80211_PARAM_WDS_SEP			= 82,	/* move wds stations into separate interfaces */
	IEEE80211_PARAM_SWITCH = 83,/*rbk new add switch*/
#endif
};
/*
 * Scan result data returned for IEEE80211_IOC_SCAN_RESULTS.
 */
 struct ieee80211req_scan_result {
	u_int16_t	isr_len;		/* length (mult of 4) */
	u_int16_t	isr_freq;		/* MHz */
	u_int32_t	isr_flags;		/* channel flags */
	u_int8_t	isr_noise;
	u_int8_t	isr_rssi;
	u_int8_t	isr_intval;		/* beacon interval */
	u_int16_t	isr_capinfo;		/* capabilities */
	u_int8_t	isr_erp;		/* ERP element */
	u_int8_t	isr_bssid[IEEE80211_ADDR_LEN];
	u_int8_t	isr_nrates;
	u_int8_t	isr_rates[IEEE80211_RATE_MAXSIZE];
	u_int8_t	isr_ssid_len;		/* SSID length */
	u_int16_t	isr_ie_len;		/* IE length */
	u_int8_t	isr_pad[4];
	/* variable length SSID followed by IE data */
};
/*
 * MLME state manipulation request.  IEEE80211_MLME_ASSOC
 * only makes sense when operating as a station.  The other
 * requests can be used when operating as a station or an
 * ap (to effect a station).
 */

struct ieee80211req_mlme {
	u_int8_t im_op;			/* operation to perform */
#define	IEEE80211_MLME_ASSOC		1	/* associate station */
#define	IEEE80211_MLME_DISASSOC		2	/* disassociate station */
#define	IEEE80211_MLME_DEAUTH		3	/* deauthenticate station */
#define	IEEE80211_MLME_AUTHORIZE	4	/* authorize station */
#define	IEEE80211_MLME_UNAUTHORIZE	5	/* unauthorize station */
#define	IEEE80211_MLME_STOP_BSS		6	/* stop bss */
#define IEEE80211_MLME_CLEAR_STATS	7	/* clear station statistic */
#define IEEE80211_MLME_AUTH	        8	/* auth resp to station */
#define IEEE80211_MLME_REASSOC	        9	/* reassoc to station */
	u_int8_t im_ssid_len;		/* length of optional ssid */
	u_int16_t im_reason;		/* 802.11 reason code */
	u_int16_t	im_seq;	        /* seq for auth */
	u_int8_t im_macaddr[MAC_ADDR_LEN];
	u_int8_t im_ssid[IEEE80211_NWID_LEN];    /* pei modified 081218 */
};

#define	IEEE80211_IOCTL_SETPARAM	(SIOCIWFIRSTPRIV+0)
#define	IEEE80211_IOCTL_GETPARAM	(SIOCIWFIRSTPRIV+1)
#define	IEEE80211_IOCTL_SETKEY		(SIOCIWFIRSTPRIV+2)
#define	IEEE80211_IOCTL_SETWMMPARAMS	(SIOCIWFIRSTPRIV+3)
#define	IEEE80211_IOCTL_DELKEY		(SIOCIWFIRSTPRIV+4)
#define	IEEE80211_IOCTL_GETWMMPARAMS	(SIOCIWFIRSTPRIV+5)
#define	IEEE80211_IOCTL_SETMLME		(SIOCIWFIRSTPRIV+6)
#define	IEEE80211_IOCTL_GETCHANINFO	(SIOCIWFIRSTPRIV+7)
#define	IEEE80211_IOCTL_SETOPTIE	(SIOCIWFIRSTPRIV+8)
#define	IEEE80211_IOCTL_GETOPTIE	(SIOCIWFIRSTPRIV+9)
#define	IEEE80211_IOCTL_ADDMAC		(SIOCIWFIRSTPRIV+10)
#define	IEEE80211_IOCTL_DELMAC		(SIOCIWFIRSTPRIV+12)
#define	IEEE80211_IOCTL_GETCHANLIST	(SIOCIWFIRSTPRIV+13)
#define	IEEE80211_IOCTL_SETCHANLIST	(SIOCIWFIRSTPRIV+14)
#define IEEE80211_IOCTL_KICKMAC		(SIOCIWFIRSTPRIV+15)
#define	IEEE80211_IOCTL_CHANSWITCH	(SIOCIWFIRSTPRIV+16)
#define	IEEE80211_IOCTL_GETMODE		(SIOCIWFIRSTPRIV+17)
#define	IEEE80211_IOCTL_SETMODE		(SIOCIWFIRSTPRIV+18)
#define IEEE80211_IOCTL_GET_APPIEBUF    (SIOCIWFIRSTPRIV+19)
#define IEEE80211_IOCTL_SET_APPIEBUF    (SIOCIWFIRSTPRIV+20)
#define IEEE80211_IOCTL_SET_ACPARAMS    (SIOCIWFIRSTPRIV+21)
#define IEEE80211_IOCTL_FILTERFRAME     (SIOCIWFIRSTPRIV+22)
#define IEEE80211_IOCTL_SET_RTPARAMS    (SIOCIWFIRSTPRIV+23)
#define IEEE80211_IOCTL_SENDADDBA       (SIOCIWFIRSTPRIV+24)
#define IEEE80211_IOCTL_GETADDBASTATUS  (SIOCIWFIRSTPRIV+25)
#define IEEE80211_IOCTL_SENDDELBA       (SIOCIWFIRSTPRIV+26)
#define IEEE80211_IOCTL_GET_IQUECONFIG  (SIOCIWFIRSTPRIV+27)
#define IEEE80211_IOCTL_SET_ADDBARESP   (SIOCIWFIRSTPRIV+28)
#define IEEE80211_IOCTL_GET_MACADDR     (SIOCIWFIRSTPRIV+29)
#define IEEE80211_IOCTL_SET_HBRPARAMS	(SIOCIWFIRSTPRIV+30)


/*
 * Summary statistics.
 */
struct ieee80211_mac_stats {
    u_int64_t   ims_tx_packets; /* frames successfully transmitted */
    u_int64_t   ims_rx_packets; /* frames successfully received */
    u_int64_t   ims_tx_bytes;	/* bytes successfully transmitted */
    u_int64_t	ims_rx_bytes;   /* bytes successfully received */

	/*pengruofeng add retry frame stats 2011-5-11*/
	u_int64_t	ims_rx_retry_packets;
	u_int64_t	ims_rx_retry_bytes;
	u_int64_t	ims_tx_retry_packets;
	u_int64_t	ims_tx_retry_bytes;
	/*pengruo add end 2011-5-11*/
	u_int64_t	ims_rx_retry_mgmt_packets;
	u_int64_t	ims_tx_retry_mgmt_packets;
	u_int64_t	ims_rx_retry_mgmt_bytes;
	u_int64_t	ims_tx_retry_mgmt_bytes;
    /* Decryption errors */
    u_int64_t   ims_rx_unencrypted; /* rx w/o wep and privacy on */
    u_int64_t   ims_rx_badkeyid;    /* rx w/ incorrect keyid */
    u_int64_t   ims_rx_decryptok;   /* rx decrypt okay */
    u_int64_t   ims_rx_decryptcrc;  /* rx decrypt failed on crc */
    u_int64_t   ims_rx_wepfail;     /* rx wep processing failed */
    u_int64_t   ims_rx_tkipreplay;  /* rx seq# violation (TKIP) */
    u_int64_t   ims_rx_tkipformat;  /* rx format bad (TKIP) */
    u_int64_t   ims_rx_tkipmic;     /* rx MIC check failed (TKIP) */
    u_int64_t   ims_rx_tkipicv;     /* rx ICV check failed (TKIP) */
    u_int64_t   ims_rx_ccmpreplay;  /* rx seq# violation (CCMP) */
    u_int64_t   ims_rx_ccmpformat;  /* rx format bad (CCMP) */
    u_int64_t   ims_rx_ccmpmic;     /* rx MIC check failed (CCMP) */
/*this file can be included by applications as 80211stats that has no such MACRO definition*/
//#if ATH_SUPPORT_WAPI 
    u_int64_t   ims_rx_wpireplay;  /* rx seq# violation (WPI) */
    u_int64_t   ims_rx_wpimic;     /* rx MIC check failed (WPI) */
//#endif
    /* Other Tx/Rx errors */
    u_int64_t   ims_tx_discard;     /* tx dropped by NIC */
    u_int64_t   ims_rx_discard;     /* rx dropped by NIC */

    u_int64_t   ims_rx_countermeasure; /* rx TKIP countermeasure activation count */
};
/*caidh move from drive for ap pkts statictics report 2013.03.07*/
struct rssi_stats{
  u_int64_t   ns_rx_data;
};

struct ieee80211_stats {
	u_int32_t	is_rx_badversion;	/* rx frame with bad version */
	u_int32_t	is_rx_tooshort;		/* rx frame too short */
	u_int32_t	is_rx_wrongbss;		/* rx from wrong bssid */
	u_int32_t	is_rx_wrongdir;		/* rx w/ wrong direction */
	u_int32_t	is_rx_mcastecho;	/* rx discard 'cuz mcast echo */
	u_int32_t	is_rx_notassoc;		/* rx discard 'cuz sta !assoc */
	u_int32_t	is_rx_noprivacy;	/* rx w/ wep but privacy off */
	u_int32_t	is_rx_decap;		/* rx decapsulation failed */
	u_int32_t	is_rx_mgtdiscard;	/* rx discard mgt frames */
	u_int32_t	is_rx_ctl;		/* rx discard ctrl frames */
	u_int32_t	is_rx_beacon;		/* rx beacon frames */
	u_int32_t	is_rx_rstoobig;		/* rx rate set truncated */
	u_int32_t	is_rx_elem_missing;	/* rx required element missing*/
	u_int32_t	is_rx_elem_toobig;	/* rx element too big */
	u_int32_t	is_rx_elem_toosmall;	/* rx element too small */
	u_int32_t	is_rx_elem_unknown;	/* rx element unknown */
	u_int32_t	is_rx_badchan;		/* rx frame w/ invalid chan */
	u_int32_t	is_rx_chanmismatch;	/* rx frame chan mismatch */
	u_int32_t	is_rx_nodealloc;	/* rx frame dropped */
	u_int32_t	is_rx_ssidmismatch;	/* rx frame ssid mismatch  */
	u_int32_t	is_rx_auth_unsupported;	/* rx w/ unsupported auth alg */
	u_int32_t	is_rx_auth_fail;	/* rx sta auth failure */
	u_int32_t	is_rx_auth_countermeasures;/* rx auth discard 'cuz CM */
	u_int32_t	is_rx_assoc_bss;	/* rx assoc from wrong bssid */
	u_int32_t	is_rx_assoc_notauth;	/* rx assoc w/o auth */
	u_int32_t	is_rx_assoc_capmismatch;/* rx assoc w/ cap mismatch */
	u_int32_t	is_rx_assoc_norate;	/* rx assoc w/ no rate match */
	u_int32_t	is_rx_assoc_badwpaie;	/* rx assoc w/ bad WPA IE */
	u_int32_t is_rx_bad_assoc;
	u_int32_t is_assoc_success;
	u_int32_t is_rx_reassoc;
	u_int32_t is_rx_reassoc_success;
	u_int32_t is_rx_bad_reassoc;
	u_int32_t is_rx_reassoc_bss;	
	u_int32_t is_rx_reassoc_notauth;	
	u_int32_t is_rx_reassoc_capmismatch;
	u_int32_t is_rx_reassoc_norate;	
	u_int32_t is_rx_reassoc_badwpaie;	
	u_int32_t is_rx_reassoc_badscie;
	
	u_int32_t is_disassoc_unnormal;
	u_int32_t is_disassoc_state;
	u_int32_t is_disassoc_ioctl;

	u_int32_t is_deauth_ioctl;
	u_int32_t is_deauth_unnormal;
	u_int32_t is_deauth_state;
	u_int32_t is_deauth_expire;
	u_int32_t	is_rx_deauth;		/* rx deauthentication */
	u_int32_t	is_rx_disassoc;		/* rx disassociation */
	u_int32_t   is_rx_action;       /* rx action mgt */
	u_int32_t	is_rx_badsubtype;	/* rx frame w/ unknown subtype*/
	u_int32_t	is_rx_nobuf;		/* rx failed for lack of buf */
	u_int32_t	is_rx_ahdemo_mgt;	/* rx discard ahdemo mgt frame*/
	u_int32_t	is_rx_bad_auth;		/* rx bad auth request */
	u_int32_t	is_rx_unauth;		/* rx on unauthorized port */
	u_int32_t	is_rx_badcipher;	/* rx failed 'cuz key type */
    u_int32_t   is_tx_nodefkey;            /* tx failed 'cuz no defkey */
    u_int32_t   is_tx_noheadroom;          /* tx failed 'cuz no space */
	u_int32_t	is_rx_nocipherctx;	/* rx failed 'cuz key !setup */
	u_int32_t	is_rx_acl;		/* rx discard 'cuz acl policy */
	u_int32_t	is_rx_ffcnt;		/* rx fast frames */
	u_int32_t	is_rx_badathtnl;   	/* driver key alloc failed */
    u_int32_t   is_rx_nowds;               /* 4-addr packets received with no wds enabled */
	u_int32_t	is_tx_nobuf;		/* tx failed for lack of buf */
	u_int32_t	is_tx_nonode;		/* tx failed for no node */
	u_int32_t	is_tx_unknownmgt;	/* tx of unknown mgt frame */
	u_int32_t	is_tx_badcipher;	/* tx failed 'cuz key type */
	u_int32_t	is_tx_ffokcnt;		/* tx fast frames sent success */
	u_int32_t	is_tx_fferrcnt;		/* tx fast frames sent success */
	u_int32_t	is_scan_active;		/* active scans started */
	u_int32_t	is_scan_passive;	/* passive scans started */
	u_int32_t	is_node_timeout;	/* nodes timed out inactivity */
	u_int32_t is_node_timeout_auth;		/*lyb add nodes timed out inactivity at auth state*/
	u_int32_t is_node_timeout_assoc;	/* lyb add nodes timed out inactivity at assoc state */
	u_int32_t	is_crypto_nomem;	/* no memory for crypto ctx */
	u_int32_t	is_crypto_tkip;		/* tkip crypto done in s/w */
	u_int32_t	is_crypto_tkipenmic;	/* tkip en-MIC done in s/w */
	u_int32_t	is_crypto_tkipdemic;	/* tkip de-MIC done in s/w */
	u_int32_t	is_crypto_tkipcm;	/* tkip counter measures */
	u_int32_t	is_crypto_ccmp;		/* ccmp crypto done in s/w */
	u_int32_t	is_crypto_wep;		/* wep crypto done in s/w */
	u_int32_t	is_crypto_setkey_cipher;/* cipher rejected key */
	u_int32_t	is_crypto_setkey_nokey;	/* no key index for setkey */
	u_int32_t	is_crypto_delkey;	/* driver key delete failed */
	u_int32_t	is_crypto_badcipher;	/* unknown cipher */
	u_int32_t	is_crypto_nocipher;	/* cipher not available */
	u_int32_t	is_crypto_attachfail;	/* cipher attach failed */
	u_int32_t	is_crypto_swfallback;	/* cipher fallback to s/w */
	u_int32_t	is_crypto_keyfail;	/* driver key alloc failed */
	u_int32_t	is_crypto_enmicfail;	/* en-MIC failed */
	u_int32_t	is_ibss_capmismatch;	/* merge failed-cap mismatch */
	u_int32_t	is_ibss_norate;		/* merge failed-rate mismatch */
	u_int32_t	is_ps_unassoc;		/* ps-poll for unassoc. sta */
	u_int32_t	is_ps_badaid;		/* ps-poll w/ incorrect aid */
	u_int32_t	is_ps_qempty;		/* ps-poll w/ nothing to send */
	u_int32_t is_rx_mgmt;
	u_int32_t is_tx_mgmt;
	u_int64_c	is_rx_mgmtbytes;
	u_int64_c	is_tx_mgmtbytes;        
	u_int32_t is_assocs;
	u_int32_t is_reassocs;
	u_int32_t is_rx_repack;		/*�ն��ش��İ���*/
	u_int32_t is_rx_rebytes;	/*�ն��ش����ֽ���*/
	u_int32_t is_rx_err_pack;				/*���յ��������ն˵Ĵ������*/
	u_int32_t is_tx_signaling;				/*���͵�ָ���ն˵��������*/
	u_int32_t is_rx_signaling;				/*�ն˴��͵��������*/
	u_int32_t is_re_wpi;/*�����طŻ��ƶ�����WPI MPDU����Ŀ*/
	u_int32_t is_wpi_mic;  /* WPI-SMS4����ʱû����Ч����Կ��������MPDU��Ŀ*/
	u_int32_t is_wpi_no_key_error;/* WPI-SMS4����ʱMICУ�������������MPDU��Ŀ*/
	u_int32_t	is_rx_auth_try;	/*add wyh@20080716 for snmp*/
	u_int32_t	is_rx_auth_ok;	/*add wyh@20080716 for snmp*/
	u_int32_t	is_rx_assoc_try;	/*add wyh@20080716 for snmp*/
	u_int32_t	is_rx_ap_too_many_sta;	/*add wyh@20080716 for snmp*/
	u_int32_t is_rx_errors;
	u_int32_t is_rx_error_frames;
	u_int32_t is_refuse_LowRssi;
	
	/*Begin: Add by zhaoej for guangdong mobile vap_rssi 2013-02-21*/
    #ifndef RSSI_RANGE_NUM
    #define RSSI_RANGE_NUM  17
    #endif
	struct rssi_stats is_rssi_stats[RSSI_RANGE_NUM];
		/*End: Add by zhaoej for guangdong mobile vap_rssi 2013-02-21*/
/*Begin:Add by zhaoenjuan for AssResp/proreq 2013-03-12*/
    u_int32_t  is_rx_probereq;
    u_int32_t  is_tx_proberesp;
    u_int32_t  is_tx_assocresp;
    u_int32_t  is_tx_reassocresp;
    u_int32_t  is_tx_authresp;
    /*end:Add by zhaoenjuan for AssResp/proreq 2013-03-12*/
};
/*
 * Per/node (station) statistics available when operating as an AP.
 */
 /*begin:add by zhaoej for guangdong mobile Rate Shaping  2013-02-19*/
/* the Terminal  and AP negotiation maximum rate*/
struct ieee80211_node_MaxRate {
 
   u_int32_t ns_rateMps;           /* Rate in Kbits per second */
//   u_int32_t ns_userRateKbps;       /* User rate in KBits per second */
//   u_int8_t  ns_rateCode;           /* rate that goes into hw descriptors */
//   u_int8_t  ns_dot11Rate;          /* Value that goes into supported rates info element of MLME */
   

};

/*End:add by zhaoej*/
struct ieee80211_nodestats {
	u_int32_t	ns_rx_data;		/* rx data frames */
	u_int32_t	ns_rx_mgmt;		/* rx management frames */
	u_int32_t	ns_rx_ctrl;		/* rx control frames */
	u_int32_t	ns_rx_ucast;		/* rx unicast frames */
	u_int32_t	ns_rx_mcast;		/* rx multi/broadcast frames */
	u_int64_c	ns_rx_bytes;		/* rx data count (bytes) */
	u_int64_c	ns_rx_beacons;		/* rx beacon frames */
	u_int32_t	ns_rx_proberesp;	/* rx probe response frames */

	u_int32_t	ns_rx_dup;		/* rx discard 'cuz dup */
	u_int32_t	ns_rx_noprivacy;	/* rx w/ wep but privacy off */
	u_int32_t	ns_rx_wepfail;		/* rx wep processing failed */
	u_int32_t	ns_rx_demicfail;	/* rx demic failed */
	u_int32_t	ns_rx_decap;		/* rx decapsulation failed */
	u_int32_t	ns_rx_defrag;		/* rx defragmentation failed */
	u_int32_t	ns_rx_disassoc;		/* rx disassociation */
	u_int32_t	ns_rx_deauth;		/* rx deauthentication */
	u_int32_t   ns_rx_action;       /* rx action */
	u_int32_t	ns_rx_decryptcrc;	/* rx decrypt failed on crc */
	u_int32_t	ns_rx_unauth;		/* rx on unauthorized port */
	u_int32_t	ns_rx_unencrypted;	/* rx unecrypted w/ privacy */

	u_int32_t	ns_tx_data;		/* tx data frames */
	u_int32_t	ns_tx_mgmt;		/* tx management frames */
	u_int32_t	ns_tx_ucast;		/* tx unicast frames */
	u_int32_t	ns_tx_mcast;		/* tx multi/broadcast frames */
	u_int64_c	ns_tx_bytes;		/* tx data count (bytes) */
	u_int32_t	ns_tx_probereq;		/* tx probe request frames */
	u_int32_t	ns_tx_uapsd;		/* tx on uapsd queue */

	u_int32_t	ns_tx_novlantag;	/* tx discard 'cuz no tag */
	u_int32_t	ns_tx_vlanmismatch;	/* tx discard 'cuz bad tag */

	u_int32_t	ns_tx_eosplost;		/* uapsd EOSP retried out */

	u_int32_t	ns_ps_discard;		/* ps discard 'cuz of age */

	u_int32_t	ns_uapsd_triggers;	     /* uapsd triggers */
	u_int32_t	ns_uapsd_duptriggers;	 /* uapsd duplicate triggers */
	u_int32_t	ns_uapsd_ignoretriggers; /* uapsd duplicate triggers */
	u_int32_t	ns_uapsd_active;         /* uapsd duplicate triggers */
	u_int32_t	ns_uapsd_triggerenabled; /* uapsd duplicate triggers */

	/* MIB-related state */
	u_int32_t	ns_tx_assoc;		/* [re]associations */
	u_int32_t	ns_tx_assoc_fail;	/* [re]association failures */
	u_int32_t	ns_tx_auth;		/* [re]authentications */
	u_int32_t	ns_tx_auth_fail;	/* [re]authentication failures*/
	u_int32_t	ns_tx_deauth;		/* deauthentications */
	u_int32_t	ns_tx_deauth_code;	/* last deauth reason */
	u_int32_t	ns_tx_disassoc;		/* disassociations */
	u_int32_t	ns_tx_disassoc_code;	/* last disassociation reason */
	u_int32_t	ns_psq_drops;		/* power save queue drops */
	u_int32_t	ns_tx_dropblock;	/* tx discard 'cuz headline block */
	u_int32_t ns_tx_ctrl;                /* tx control frames */
	/*zhaoyang modify for wapi error frame count*/
	u_int32_t ns_re_wpi;/*�����طŻ��ƶ�����WPI MPDU����Ŀ*/
	u_int32_t ns_wpi_mic;  /* WPI-SMS4����ʱû����Ч����Կ��������MPDU��Ŀ*/
	u_int32_t ns_wpi_no_key_error;/* WPI-SMS4����ʱMICУ�������������MPDU��Ŀ*/
	/*zhaoyang modify end*/
	u_int32_t ns_tx_retry_packets;
	u_int32_t ns_tx_retry_bytes;
	u_int32_t ns_rx_retry_packets;
	u_int32_t ns_rx_retry_bytes;
	u_int64_c	ns_rx_bytes_l;            /*  rx data count (bytes) of last time */
	u_int64_c	ns_sum_bytes;            /*  rx and tx data sum (bytes) of last time */
	
	u_int32_t ns_tx_frag;
	u_int32_t ns_rx_frag;
	unsigned long  ns_time_remain;      /*  rx data count (bytes) of last time */ 
	/*Begin:pengdecai @ record rssi states @20120427*/
#ifndef RSSI_RANGE_NUM
#define RSSI_RANGE_NUM  17
#endif
	struct rssi_stats  ns_rssi_stats[RSSI_RANGE_NUM];
	/*End:pengdecai @ record rssi states @20120427*/
    	struct ieee80211_node_MaxRate ns_MaxRates; //add by zhaoej for guangdong mobile rate sharping 2013-02-19
};
/*
 * Retrieve per-node statistics.
 */
struct ieee80211req_sta_stats {
	union {
		/* NB: explicitly force 64-bit alignment */
		u_int8_t macaddr[IEEE80211_ADDR_LEN];
		u_int64_c pad;
	} is_u;
	struct ieee80211_nodestats is_stats;
};

struct ieee80211req_sta_info {
	u_int16_t	isi_len;		/* length (mult of 4) */
	u_int16_t	isi_freq;		/* MHz */
	u_int32_t   isi_flags;      /* channel flags */
	u_int16_t	isi_state;		/* state flags */
	u_int8_t	isi_authmode;		/* authentication algorithm */
	int8_t	    	isi_rssi;
	u_int16_t	isi_capinfo;		/* capabilities */
	u_int8_t	isi_athflags;		/* Atheros capabilities */
	u_int8_t	isi_erp;		/* ERP element */
	u_int8_t	isi_macaddr[IEEE80211_ADDR_LEN];
	u_int8_t	isi_nrates;
						/* negotiated rates */
	u_int8_t	isi_rates[IEEE80211_RATE_MAXSIZE];
	u_int8_t	isi_txrate;		/* index to isi_rates[] */
	u_int32_t	isi_txratekbps;         /* tx rate in kbps */
	u_int32_t	isi_rxratekbps;         /* rx rate in kbps */
	u_int16_t	isi_ie_len;		/* IE length */
	u_int16_t	isi_associd;		/* assoc response */
	u_int16_t	isi_txpower;		/* current tx power */
	u_int16_t	isi_vlan;		/* vlan tag */
	u_int16_t	isi_txseqs[17];		/* seq to be transmitted */
	u_int16_t	isi_rxseqs[17];		/* seq previous for qos frames*/
	u_int16_t	isi_inact;		/* inactivity timer */
	u_int8_t	isi_uapsd;		/* UAPSD queues */
	u_int8_t	isi_opmode;		/* sta operating mode */
	u_int8_t	isi_cipher;
	u_int32_t	isi_assoc_time;	/* sta association time */

	u_int16_t	isi_htcap;		/* HT capabilities */
	/* XXX frag state? */
	/* variable length IE data */
};

/*******************ieee80211_node.h**************************************/
/* pei add for gather station info at 090417 */
#define	IEEE80211_NODE_AUTH	0x0001		/* authorized for data */
#define	IEEE80211_NODE_QOS	0x0002		/* QoS enabled */
#define	IEEE80211_NODE_ERP	0x0004		/* ERP enabled */
/* NB: this must have the same value as IEEE80211_FC1_PWR_MGT */
#define	IEEE80211_NODE_PWR_MGT	0x0010		/* power save mode enabled */
#define	IEEE80211_NODE_AREF	0x0020		/* authentication ref held */
#define IEEE80211_NODE_UAPSD	0x0040		/* U-APSD power save enabled */
#define IEEE80211_NODE_UAPSD_TRIG 0x0080	/* U-APSD triggerable state */
#define IEEE80211_NODE_UAPSD_SP	0x0100		/* U-APSD SP in progress */
//#endif


/*Start: Add by zhanghu to statistics of every frame by the rate*/
#ifndef RATE_FRAME_INFO
#define RATE_FRAME_INFO

struct rate_info{
    u_int64_t    count;
    u_int8_t    dot11Rate;
};

struct mac_rate_frame_info{
    struct rate_info    rate[12];
    u_int64_t   mcs[24];
};


struct iw_vap_rate_frame_req{    
    u_int8_t    mac[6];
    struct mac_rate_frame_info vap_rx_data;    
    struct mac_rate_frame_info vap_tx_data;
	
#ifndef RSSI_RANGE_NUM
#define RSSI_RANGE_NUM  17
#endif
	
	struct rssi_stats	vap_rssi_stats[RSSI_RANGE_NUM];
	 /*End : add by zhaoej*/
};

struct ni_info {    
    u_int8_t    mac[6];
    struct  mac_rate_frame_info ni_rx_data;
    struct  mac_rate_frame_info ni_tx_data;

#ifndef RSSI_RANGE_NUM
#define RSSI_RANGE_NUM  17
#endif

    struct rssi_stats   ni_rssi_stats[RSSI_RANGE_NUM];
};



struct iw_ni_rate_frame_req{
    u_int32_t   ni_count;

#ifndef NI_COUNT
#define NI_COUNT    128
#endif

    struct ni_info ni_data[128];
};

#endif

/*End: Add by zhanghu to statistics of every frame by the rate*/

/*Start: Add by zhanghu to statistics of every frame by the rate*/
#define SIOCSIWNIRATEFRAME   0x8B3A    /*statistics of every frame by the rate*/    
#define SIOCGIWNIRATEFRAME   0x8B3B

#define SIOCSIWVAPRATEFRAME   0x8B38    /*statistics of every frame by the rate*/    
#define SIOCGIWVAPRATEFRAME   0x8B39
/*End: Add by zhanghu to statistics of every frame by the rate*/

typedef enum{
	ACL_CLASS_WHITELIST = 1,
	ACL_CLASS_BLACKLIST = 2
}ACLClass;

typedef enum{
	ACL_LEVEL_AP = 0,
	ACL_LEVEL_RADIO = 1,
	ACL_LEVEL_WLAN = 2
}ACKLevel;
typedef enum{
	ACL_OP_ADD = 0,
	ACL_OP_DEL = 1,
	ACL_OP_COVER = 2,
	ACL_OP_CLEAR = 3
}ACLOp;
extern CWBool CWGetConfigFromFile(char filepath[128],char filename[64],char * str);
CWBool CWSetMultiUserPerformance(GetMultiUserPerformanceValues *MultiUserPerformanceValues);
CWBool CWSetMcsMask(GetMcsMaskValues *McsMaskValues);
CWBool CWSetStaThroughput(StaThroughputSetValues *staThroughputSetValues);
CWBool CWSetStaPktsStatisticRpt(GetStaPktsStatisticRptValues *getStaPktsStatisticRptValues);
CWBool CWSetEMenuConf(EMenuConf *conf);
CWBool CWSetACLList(GetACLList *conf);
CWBool CWXmlWriteRadioParam(char *file, int radio_id, char *arg_name, char *arg_val);
CWBool CWXmlWriteWlanParam(char *file, int radio_id, int wlan_id, char *arg_name, char *arg_val);
CWBool CWXmlWriteWlanACLMac(int radio_id, int wlan_id, char *listname, int total_count, int index, unsigned char *mac);
char *CWGetXmlNodeValue(char *node_name, char* ret);
/* Begin: gengzj added for wifipos 2013-11-25 */
CWBool CWWTPInitScanPosSock(CWSocket* scanpos_sock);
CWBool CWWTPStopDetector(void);
CWBool CWWTPStartDetector(void);
CWBool CWWTPStopDetectorMonitor(void);
CWBool CWWTPStartDetectorMonitor(void);
#ifdef _SCANPOS_RESULT_REPORT_
CWBool CWWTPCommonSendMessageToAC(int fragmentsNum, CWProtocolMessage* messages);
#endif /* _SCANPOS_RESULT_REPORT_ */
/* End: gengzj added end */
#endif
