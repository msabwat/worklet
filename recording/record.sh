#!/bin/bash
# Based on https://www.pantz.org/software/alsa/recording_sound_from_your_web_browser_using_linux.html
# Run `pulseaudio -k` before


FILENAME="$1"
STOPTIME="$2"
FLACOPTIONS="--force-raw-format --endian=little --channels=2 --sample-rate=44100 --sign=signed --bps=16 -f"

# Get Sink Monitor

MONITOR=$(pactl list | egrep -A2 '^(\*\*\* )?Source #' | \
    grep 'Name: .*\.monitor$' | awk '{print $NF}' | tail -n1)
echo "set-source-mute ${MONITOR} false" | pacmd >/dev/null

echo -e "\nStopping in $STOPTIME seconds"
parec -d $MONITOR | flac - $FLACOPTIONS -o $FILENAME 2>&1 &
SPID=$!
sleep $STOPTIME
kill -9 $SPID

