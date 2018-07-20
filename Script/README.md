# This tool was forked from fslack.py located at: https://github.com/marek/fslack
# This script was refactored by Cody Sigvartson to support the CougsInSpace slack channel.

# Last modified: 7/19/2018

# Change log:
# Initial commit (6/29/2018): the script supported downloading all public files
# Added deletion feature (7/19/2018): script is capable of deleting all files on slack

### Requirements

* [Slack API Token] - Get it from https://api.slack.com/web and pass it via --token
* [Python] - The app is written in python3
* [requests] - web request library for python

### Usage Instructions

get an api token from https://api.slack.com/web. If you have problems with this please ask Cody Sigvartson.

Command line instruction:

Download all files:
fslack.py --download --all --out <filename> <token>

Delete all files:
fslack.py --delete -all <token>


** Note: output folder must exist prior to calling the command


