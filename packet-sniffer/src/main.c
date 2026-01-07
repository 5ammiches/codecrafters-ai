/*
 * Packet Sniffer - Stage 1
 *
 * Goal: Initialize libpcap and capture packets
 *
 * TODO: Implement the following:
 * 1. Find a network device to capture on
 * 2. Open the device for live capture
 * 3. Start capturing packets in a loop
 * 4. Print "Packet captured!" for each packet
 * 5. Clean up resources when done
 *
 * Hint: Start by reading `man pcap`
 */

#include <arpa/inet.h>
#include <netinet/in.h>
#include <pcap/pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_sa_family_t.h>
#include <sys/_types/_timeval.h>
#include <sys/_types/_u_char.h>
#include <sys/socket.h>

void format_bytes(unsigned int bytes, char *output, size_t output_size) {
  if (bytes >= 1024 * 1024) {
    snprintf(output, output_size, "%.2f MB", bytes / (1024.0 * 1024.0));
  } else if (bytes >= 1024) {
    snprintf(output, output_size, "%.2f KB", bytes / 1024.0);
  } else {
    snprintf(output, output_size, "%u bytes", bytes);
  }
}

void packet_handler(u_char *user, const struct pcap_pkthdr *hdr,
                    const u_char *bytes) {
  struct tm *ltime;
  char timestr[64];
  // char size_str[32];
  time_t local_tv_sec;

  local_tv_sec = hdr->ts.tv_sec;
  ltime = localtime(&local_tv_sec);

  strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", ltime);

  printf("Packet captured!\n");
  // if (user != NULL) {
  //   char *device = (char *)user;
  //   printf("Captured on device: %s\n", device);
  // }

  // printf("[%s.%06ld] Packet captured\n", timestr, (long)hdr->ts.tv_usec);

  // format_bytes(hdr->caplen, size_str, sizeof(size_str));
  // printf("  Captured length: %s\n (%u bytes)", size_str, hdr->caplen);

  // format_bytes(hdr->len, size_str, sizeof(size_str));
  // printf("  Packet length: %s (%u bytes) \n", size_str, hdr->len);
  // printf("\n");
}

int main(int argc, char *argv[]) {

  setbuf(stdout, NULL);
  printf("Packet Sniffer - Stage 1\n");
  printf("TODO: Implement packet capture\n");

  /* Your implementation goes here */
  char errbuf[PCAP_ERRBUF_SIZE];
  int status;
  pcap_if_t *alldevsp;
  pcap_t *dev;
  u_char *user = NULL;

  pcap_init(PCAP_CHAR_ENC_LOCAL, errbuf);

  int res = pcap_findalldevs(&alldevsp, errbuf);

  if (res < 0) {
    printf("An error occurred: %s\n", errbuf);
    return 1;
  }

  if (res == 0) {
    if (alldevsp == NULL) {
      printf("Success, but no devices found.\n");
    } else {
      printf("first device: %s\n", alldevsp->name);
      // printf("devices found:\n\n");
      // for (pcap_if_t *p = alldevsp; p != NULL; p = p->next) {
      //   printf("%s\n", p->name);
      //   printf("addresses:\n");
      //   for (pcap_addr_t *a = p->addresses; a != NULL; a = a->next) {
      //     struct sockaddr *sa = a->addr;

      //     if (sa->sa_family == AF_INET) {
      //       struct sockaddr_in *ipv4 = (struct sockaddr_in *)sa;

      //       char ip_str[INET_ADDRSTRLEN];
      //       inet_ntop(AF_INET, &(ipv4->sin_addr), ip_str, INET_ADDRSTRLEN);
      //       printf("IPv4 address: %s\n", ip_str);
      //     } else if (sa->sa_family == AF_INET6) {
      //       struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)sa;

      //       char ip_str[INET_ADDRSTRLEN];
      //       inet_ntop(AF_INET, &(ipv6->sin6_addr), ip_str, INET_ADDRSTRLEN);
      //       printf("IPv6 address: %s\n", ip_str);
      //     }
      //   }
      //   printf("\n");
      // }
    }
  }

  dev = pcap_create(alldevsp->name, errbuf);
  if (dev == NULL) {
    printf("An error occurred: %s\n", errbuf);
    return 1;
  }

  pcap_set_timeout(dev, 1000);

  status = pcap_activate(dev);
  if (status >= 0) {
    int num_of_packets = pcap_loop(dev, 0, packet_handler, user);
    if (num_of_packets < 0) {
      pcap_perror(dev, "An error occurred when processing packets");
      return 1;
    }
  } else if (status < 0) {
    pcap_perror(dev, "An error/warning occurred");
    return 1;
  }

  pcap_close(dev);
  pcap_freealldevs(alldevsp);

  return 0;
}
