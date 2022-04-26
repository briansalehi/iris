#!/usr/bin/env bash

readarray -t displays <<< "$(find /sys/class/backlight -maxdepth 1 -mindepth 1 -exec basename {} \;)"

while [ "$#" -gt 0 ]
do
    case "$1" in
        -d|--display) selected_display="$2"; shift ;;
        [-+][0-9]*) percent="$1" ;;
        [0-9]*) percent="$1" ;;
        *) echo "usage: adjust-brightness [percentage]"; exit 255 ;;
    esac
    shift
done

if [ "${#displays[@]}" -gt 1 ] && [ "$selected_display" == "" ]
then
    select selected_display in "${displays[@]}"; do break; done

    if ! [[ "${displays[*]}" == *"$selected_display"* ]]
    then
        echo -e "\e[31m]Could not find brightness range correctly\e[0m"
        exit 1
    fi
elif [ "$selected_display" == "" ]
then
    selected_display="${displays[0]}"
fi

max_brightness="$(< "/sys/class/backlight/$selected_display/max_brightness")"
brightness="$(< "/sys/class/backlight/$selected_display/brightness")"

if [ "$brightness" == "" ] || [ "$max_brightness" == "" ] || [ "$max_brightness" -le 0 ] || [ "$brightness" -lt 0 ] || [ "$brightness" -gt "$max_brightness" ]
then
    echo -e "\e[31m]Could not find brightness range correctly\e[0m"
    exit 2
elif [ "$percent" == "" ]
then
    echo "$((brightness * 100 / max_brightness))"
    exit 0
elif [[ "${percent}" == [-+][0-9]* ]] && [ "$(($((brightness * 100 / max_brightness)) + percent))" -gt "100" ]
then
    percent="100"
elif [[ "${percent}" == [-+][0-9]* ]] && [ "$(($((brightness * 100 / max_brightness)) + percent))" -le "0" ]
then
    percent="1"
elif [[ "${percent}" == [0-9]* ]] && [ "$(($((brightness * 100 / max_brightness)) + percent))" -gt "100" ]
then
    percent="100"
elif [[ "${percent}" == [0-9]* ]] && [ "$(($((brightness * 100 / max_brightness)) + percent))" -le "0" ]
then
    percent="1"
fi

case "$percent" in
    [-+][0-9]*) echo "$(($((brightness * 100 / max_brightness + percent)) * max_brightness / 100))" > "/sys/class/backlight/${displays[$selected_display]}/brightness" ;;
    [0-9]*) echo "$((percent * max_brightness / 100))" > "/sys/class/backlight/${displays[$selected_display]}/brightness" ;;
    *) echo -e "\e[31m]Range not within (0~100]\e[0m"; exit 3 ;;
esac
