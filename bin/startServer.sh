#!/bin/bash
until "./server"; do
    echo "Server 'MayaScape' crashed with exit code $?.  Respawning.." >&2
    sleep 1
done
