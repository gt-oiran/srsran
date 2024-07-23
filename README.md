srsRAN Project
==============

[![Build Status](https://github.com/srsran/srsRAN_Project/actions/workflows/ccpp.yml/badge.svg?branch=main)](https://github.com/srsran/srsRAN_Project/actions/workflows/ccpp.yml)
[![OpenSSF Best Practices](https://www.bestpractices.dev/projects/7868/badge)](https://www.bestpractices.dev/projects/7868)

The srsRAN Project is a complete 5G RAN solution, featuring an ORAN-native CU/DU developed by [SRS](http://www.srs.io).

The solution includes a complete L1/2/3 implementation with minimal external dependencies. Portable across processor architectures, the software has been optimized for x86 and ARM. srsRAN follows the 3GPP 5G system architecture implementing the functional splits between distributed unit (DU) and centralized unit (CU). The CU is further disaggregated into control plane (CU-CP) and user-plane (CU-UP).

See the [srsRAN Project](https://www.srsran.com/) for information, guides and project news.

Build instructions and user guides - [srsRAN Project documentation](https://docs.srsran.com/projects/project).

Community announcements and support - [Discussion board](https://www.github.com/srsran/srsran_project/discussions).

Features and roadmap - [Features](https://docs.srsran.com/projects/project/en/latest/general/source/2_features_and_roadmap.html).

Build Preparation
-----------------

* Build tools:
  * cmake:               <https://cmake.org/>
  
* Mandatory requirements:
  * libfftw:             <https://www.fftw.org/>
  * libsctp:             <https://github.com/sctp/lksctp-tools>
  * yaml-cpp:            <https://github.com/jbeder/yaml-cpp>
  * mbedTLS:             <https://www.trustedfirmware.org/projects/mbed-tls/>
  * googletest:          <https://github.com/google/googletest/>

You can install the build tools and mandatory requirements for some example distributions with the commands below:

<details open>
<summary>Ubuntu 22.04</summary>

```bash
sudo apt-get install cmake make gcc g++ pkg-config libfftw3-dev libmbedtls-dev libsctp-dev libyaml-cpp-dev libgtest-dev
```

</details>
<details>
<summary>Fedora</summary>

```bash
sudo yum install cmake make gcc gcc-c++ fftw-devel lksctp-tools-devel yaml-cpp-devel mbedtls-devel gtest-devel
```

</details>
<details>
<summary>Arch Linux</summary>

```bash
sudo pacman -S cmake make base-devel fftw mbedtls yaml-cpp lksctp-tools gtest
```

</details>

The srsRAN Project supports split-8 and split-7.2 fronthaul.

Split-8 fronthaul is supported via UHD for USRP devices.

* UHD:                 <https://github.com/EttusResearch/uhd>
  * See UHD documentation for installation instructions.

Split-7.2 is supported via DPDK:

* DPDK:                <https://www.dpdk.org/>

Build Instructions
------------------

Download and build srsRAN:

```bash
git clone https://github.com/srsran/srsRAN_Project.git
cd srsRAN_Project
mkdir build
cd build
cmake ..
make
make test
```

PHY layer tests use binary test vectors and are not built by default. To enable, see the [docs](https://docs.srsran.com/projects/project/en/latest/user_manuals/source/installation.html).

How to deploy a 5G network?
----------------------------------------------

Check our [tutorials](https://docs.srsran.com/projects/project/en/latest/tutorials/source/index.html) that describe how to set up an end-to-end 5G SA system with srsRAN Project.

[OIRAN] Exposed metrics for e2sm_kpm
----------------------------------------------

| **Metric** | **Description** |
|-------------|---------------|
| PCI         | Physical Cell Identifier |
| RNTI        | Radio Network Temporary Identifier (UE identifier) |
| McsDl       | Dl Modulation and coding scheme (0-28) |
| McsUl       | Ul Modulation and coding scheme (0-28) |
| BrateDl     | Dl bitrate in kbps |
| BrateUl     | Ul bitrate in kbps |
| NofOkDl     | Dl Number of packets successfully sent |
| NofNOkDl    | Dl Number of packets dropped |
| NofOkUl     | Ul Number of packets successfully sent |
| NofNOkUl    | Ul Number of packets dropped |
| SNR         | PUSCH SINR (Signal-to-Interference-plus-Noise Ratio) |
| RSRP        | Reference Signal Received Power |
| BSR         | Buffer Status Report, data waiting to be transmitted as reported by the UE (bytes) |
| BSDl        | Downlink Buffer Status, data waiting to be transmitted as reported by the gNB (bytes) |
| TA          | Timing Advance in microseconds |
| PHR         | Power Headroom as reported by the UE |
| CQI         | Channel Quality Indicator reported by the UE (1-15) |
| RA          | Rank Indicator as reported by the UE |
| DRB.UEThpDl | DL throughput |
| DRB.UEThpUl | UL throughput |
| DRB.RlcPacketDropRateDl | UL packet success rate |
| DRB.PacketSuccessRateUlgNBUu | RLC DL packet drop rate |
| DRB.RlcSduTransmittedVolumeDL | RLC DL transmitted SDU volume |
| DRB.RlcSduTransmittedVolumeUL | RLC UL transmitted SDU volume |
