#!/bin/bash

HERMIT_ISLE=uhyve \
HERMIT_IP="10.0.5.3" \
HERMIT_GATEWAY="10.0.5.1" \
HERMIT_MASk="255.255.255.0" \
HERMIT_NETIF=tap100 \
/opt/hermit/bin/proxy build/ServerLight
